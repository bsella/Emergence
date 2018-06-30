#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow){
	ui->setupUi(this);
	QWidget::setWindowTitle("Emergence");
	QWidget::setWindowIcon(QIcon(":/icons/emgc.ico"));

	ui->workspace->setScene(new QGraphicsScene);
	scene=ui->workspace->scene();

	connect(ui->actionCopy,SIGNAL(triggered(bool)),this,SLOT(copy()));
	connect(ui->actionPaste,SIGNAL(triggered(bool)),this,SLOT(paste()));
	connect(ui->actionCut,SIGNAL(triggered(bool)),this,SLOT(cut()));
	connect(ui->actionDelete,SIGNAL(triggered(bool)),this,SLOT(delete_selected()));
	connect(ui->actionSelect_all,SIGNAL(triggered(bool)),this,SLOT(select_all()));

	connect(ui->actionSave_as,SIGNAL(triggered(bool)),this,SLOT(save()));
	connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(load()));

	undoStack=new QUndoStack(this);

	connect(ui->actionUndo,SIGNAL(triggered(bool)),undoStack,SLOT(undo()));
	connect(ui->actionRedo,SIGNAL(triggered(bool)),undoStack,SLOT(redo()));
	ui->actionUndo->setEnabled(false); ui->actionRedo->setEnabled(false);
	connect(undoStack,SIGNAL(canUndoChanged(bool)),ui->actionUndo,SLOT(setEnabled(bool)));
	connect(undoStack,SIGNAL(canRedoChanged(bool)),ui->actionRedo,SLOT(setEnabled(bool)));

	connect(ui->workspace,SIGNAL(dropped(QDropEvent*)),this,SLOT(drop(QDropEvent*)));
	connect(scene,SIGNAL(selectionChanged()),this,SLOT(updateActions()));

	Node* y= nodeMalloc(Y_G);
	y->setPos(0,100);
	y->initialPos={0,100};
	Node* out= nodeMalloc(RENDER_G);
	out->setPos(100,50);
	out->initialPos={100,50};
	QList<Node*> initList;
	initList.append(nodeMalloc(X_G));
	initList.append(y);
	initList.append(out);
	addNodes(initList);
	scene->clearSelection();
}
MainWindow::~MainWindow(){
	delete undoStack;
	delete ui->workspace;
	delete ui;
}

Node* MainWindow::nodeMalloc(uint g, void* arg){
	switch(g){
	case DOUBLE_G:{
		if(arg) return new ConstNode(*(double*)arg);
		bool ok;
		double d =QInputDialog::getDouble(this,"Choose Number","",0,-2147483647,2147483647,3,&ok);
		if(!ok) return nullptr;
		return new ConstNode(d);
	}
	case COLOR_G:{
		if(arg) return new ConstNode(*(data_t::color*)arg);
		QColor c=QColorDialog::getColor(Qt::white,this);
		if(!c.isValid()) return nullptr;
		return new ConstNode(c.rgba());
	}
	case PALETTE_G:{
		///TODO : Implement dialog for palette
		Palette p;
		p.add(0xffff0000,0);
		p.add(0xff0000ff,.5);
		p.add(0xff00ff00,1);
		return new LUTNode(p);
	}
	case BITMAP_G:{
		QString f;
		if(arg) f=*(QString*)arg;
		else{
			f= QFileDialog::getOpenFileName(this,"Choose Image",".","Images (*.bmp)");
			if(f.isNull())return nullptr;
		}
		return new BitmapNode(f);
	}
	case IF_G:		return new IfNode;
	case GT_G:		return new GTNode;
	case LT_G:		return new LTNode;
	case EQ_G:		return new EQNode;
	case NE_G:		return new NENode;
	case OR_G:		return new ORNode;
	case AND_G:		return new ANDNode;
	case XOR_G:		return new XORNode;
	case NOT_G:		return new NOTNode;
	case ADD_G:		return new ADDNode;
	case SUB_G:		return new SUBNode;
	case MUL_G:		return new MULNode;
	case DIV_G:		return new DIVNode;
	case NEG_G:		return new NEGNode;
	case SQRT_G:	return new SQRTNode;
	case ABS_G:		return new ABSNode;
	case LERP_G:	return new LERPNode;
	case CLAMP_G:	return new CLAMPNode;
	case SIN_G:		return new SINNode;
	case COS_G:		return new COSNode;
	case MIN_G:		return new MINNode;
	case MAX_G:		return new MAXNode;
	case RGB_G:		return new RGBNode;
	case HSV_G:		return new HSVNode;
	case CPLX_G:	return new ComplexNode;
	case X_G:		return new PixelXNode;
	case Y_G:		return new PixelYNode;
	case RENDER_G:	return new RenderNode;
	case RATIO_G:	return new RatioNode;
	default:return nullptr;
	}
}

void MainWindow::drop(QDropEvent *event){
	addNode(nodeMalloc(event->mimeData()->data("type").toInt()),
				ui->workspace->mapToScene(event->pos()));
}

void MainWindow::copy()const{
	QMimeData * mime=new QMimeData;
	mime->setText("Emergence_Nodes");
	mime->setData("copy",nodesToText(scene->selectedItems()));
	QApplication::clipboard()->setMimeData(mime);
}

void MainWindow::cut(){
	copy();
	delete_selected();
}

void MainWindow::paste(){
	scene->clearSelection();
	const QMimeData* mime= QApplication::clipboard()->mimeData();
	if(mime->text()=="Emergence_Nodes")
		addNodes(textToNodes(mime->data("copy")));
}

void MainWindow::select_all() const{
	for(auto& n : scene->items())
		n->setSelected(true);
}

void MainWindow::delete_selected(){
	undoStack->beginMacro("delete");
	for(auto& n:scene->selectedItems())
		undoStack->push(new DeleteNodeCommand((Node*)n,scene));
	undoStack->endMacro();
}

QByteArray MainWindow::nodesToText(const QList<QGraphicsItem*> &nodes) const{
	QByteArray ret;
	QDataStream ds (&ret,QIODevice::Append);
	ds<<nodes.size();
	for(const auto& i:nodes){
		Node* n=(Node*)i;
		ds<<n->id;
		ds<<n->scenePos().x();
		ds<<n->scenePos().y();
		if(n->id==DOUBLE_G)
			ds<<n->val.d;
		else if(n->id==COLOR_G)
			ds<<n->val.clr;
	}
	for(const auto& n : nodes)
		for(const auto& nn: ((Node*)n)->iNodes)
			ds<<nodes.indexOf(nn);
	return ret;
}

QList<Node*> MainWindow::textToNodes(const QByteArray &ba){
	QDataStream ds(ba);
	int n; ds>>n;
	int id; float x,y;
	QList<Node*> newNodes;
	for(int i=0; i<n; i++){
		ds>>id;
		ds>>x;
		ds>>y;
		void* arg=nullptr;
		if(id==DOUBLE_G){
			double d;
			ds>>d;
			arg=&d;
		}else if(id==COLOR_G){
			data_t::color c;
			ds>>c;
			arg=&c;
		}
		newNodes.append(nodeMalloc(id,arg));
		newNodes.back()->setPos(x,y);
	}
	for(auto& node: newNodes)
		for(unsigned i=0; i<node->nbArgs; i++){
			ds>>n;
			if(n>=0)
				node->sockets[i]->connectToNode(newNodes.at(n));
		}
	return newNodes;
}

void MainWindow::save()const{
	QString fileName= QFileDialog::getSaveFileName(ui->workspace,"Save as...",".","Node Files (*.emrg)");
	if(fileName.isEmpty()) return;
	if(!fileName.endsWith(".emrg"))
		fileName.append(".emrg");
	QFile file(fileName);
	if(!file.open(QIODevice::WriteOnly)){
		QMessageBox::information(ui->workspace,"Unable to open file",file.errorString());
		return;
	}
	file.resize(0);
	QDataStream out(&file);

	out << MAGIC_NUMBER;
	out << SAVE_VERSION;

	select_all();
	out << nodesToText(scene->selectedItems());
	scene->clearSelection();
	file.close();
}

void MainWindow::load(){
	QString f= QFileDialog::getOpenFileName(parentWidget(),"Open File",".","Node Files (*.emrg)");
	if(f.isNull()) return;
	QFile file(f);
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);
	uint magic; in>>magic;
	if(magic!=MAGIC_NUMBER){
		QMessageBox::warning(0,"Wrong format","Bad File Format");
		return;
	}
	uint version; in>>version;
	if(version<SAVE_VERSION){
		QMessageBox::warning(0,"Wrong version","Sorry, this save file is too old.");
		return;
	}
	in.skipRawData(4);

	select_all();
	undoStack->beginMacro("load");
	delete_selected();
	addNodes(textToNodes(file.readAll()));
	undoStack->endMacro();
	scene->clearSelection();
}

void MainWindow::addNode(Node *n){
	addNode(n,scene->sceneRect().center());
}

void MainWindow::addNode(Node *n, const QPointF& pos){
	if(!n) return;
	n->setPos(pos);
	n->initialPos=pos;
	connect(n,SIGNAL(moved()),this,SLOT(moveNodes()));
	connect(n,SIGNAL(connected(Node::Socket*,Node*)),this,SLOT(connectNode(Node::Socket*,Node*)));
	connect(n,SIGNAL(disconnected(Node::Socket*)),this,SLOT(disconnectNode(Node::Socket*)));
	connect(n->actionDelete,&QAction::triggered,this,[=](){undoStack->push(new DeleteNodeCommand(n,scene));});
	undoStack->push(new AddNodeCommand(n,scene));
}

void MainWindow::addNodes(const QList<Node *> &n){
	undoStack->beginMacro("add_node");
	for(auto& i: n){
		if(!i) continue;
		i->initialPos=i->pos();
		connect(i,SIGNAL(moved()),this,SLOT(moveNodes()));
		connect(i,SIGNAL(connected(Node::Socket*,Node*)),this,SLOT(connectNode(Node::Socket*,Node*)));
		connect(i,SIGNAL(disconnected(Node::Socket*)),this,SLOT(disconnectNode(Node::Socket*)));
		connect(i->actionDelete,&QAction::triggered,this,[=](){undoStack->push(new DeleteNodeCommand(i,scene));});
		undoStack->push(new AddNodeCommand(i,scene));
	}
	undoStack->endMacro();
}

void MainWindow::moveNodes(){
	undoStack->beginMacro("move");
	for(auto& n: ui->workspace->scene()->selectedItems())
		undoStack->push(new MoveNodeCommand((Node*)n));
	undoStack->endMacro();
}

void MainWindow::connectNode(Node::Socket* s, Node* n){
	undoStack->push(new ConnectNodeCommand(s,n));
}
void MainWindow::disconnectNode(Node::Socket* s){
	undoStack->push(new DisconnectNodeCommand(s));
}

void MainWindow::on_actionExit_triggered(){
	close();
}
void MainWindow::updateActions(){
	ui->actionExport->setEnabled(false);
	for(auto& n: scene->selectedItems())
		if(((Node*)n)->id==RENDER_G && *((RenderNode*)n)){
			ui->actionExport->setEnabled(true);
			break;
		}
}
void MainWindow::on_actionExport_triggered(){
	for(const auto& n: scene->selectedItems())
		if(((Node*)n)->id==RENDER_G && *((RenderNode*)n))
			ExportImageDialog::exportBMP((RenderNode*)n);
}
void MainWindow::on_actionIf_triggered(){
	addNode(nodeMalloc(IF_G));
}
void MainWindow::on_actionGreaterThan_triggered(){
	addNode(nodeMalloc(GT_G));
}
void MainWindow::on_actionLessThan_triggered(){
	addNode(nodeMalloc(LT_G));
}
void MainWindow::on_actionEqual_triggered(){
	addNode(nodeMalloc(EQ_G));
}
void MainWindow::on_actionNot_Equal_triggered(){
	addNode(nodeMalloc(NE_G));
}
void MainWindow::on_actionAND_triggered(){
	addNode(nodeMalloc(AND_G));
}
void MainWindow::on_actionOR_triggered(){
	addNode(nodeMalloc(OR_G));
}
void MainWindow::on_actionXOR_triggered(){
	addNode(nodeMalloc(XOR_G));
}
void MainWindow::on_actionNOT_triggered(){
	addNode(nodeMalloc(NOT_G));
}
void MainWindow::on_actionDouble_triggered(){
	addNode(nodeMalloc(DOUBLE_G));
}
void MainWindow::on_actionColor_triggered(){
	addNode(nodeMalloc(COLOR_G));
}
void MainWindow::on_actionLUT_triggered(){
	addNode(nodeMalloc(PALETTE_G));
}
void MainWindow::on_actionX_triggered(){
	addNode(nodeMalloc(X_G));
}
void MainWindow::on_actionY_triggered(){
	addNode(nodeMalloc(Y_G));
}
void MainWindow::on_actionRender_triggered(){
	addNode(nodeMalloc(RENDER_G));
}
void MainWindow::on_actionADD_triggered(){
	addNode(nodeMalloc(ADD_G));
}
void MainWindow::on_actionSUB_triggered(){
	addNode(nodeMalloc(SUB_G));
}
void MainWindow::on_actionMUL_triggered(){
	addNode(nodeMalloc(MUL_G));
}
void MainWindow::on_actionDIV_triggered(){
	addNode(nodeMalloc(DIV_G));
}
void MainWindow::on_actionNEG_triggered(){
	addNode(nodeMalloc(NEG_G));
}
void MainWindow::on_actionSQRT_triggered(){
	addNode(nodeMalloc(SQRT_G));
}
void MainWindow::on_actionABS_triggered(){
	addNode(nodeMalloc(ABS_G));
}
void MainWindow::on_actionLerp_triggered(){
	addNode(nodeMalloc(LERP_G));
}
void MainWindow::on_actionClamp_triggered(){
	addNode(nodeMalloc(CLAMP_G));
}
void MainWindow::on_actionBitmap_triggered(){
	addNode(nodeMalloc(BITMAP_G));
}
void MainWindow::on_actionSin_triggered(){
	addNode(nodeMalloc(SIN_G));
}
void MainWindow::on_actionCos_triggered(){
	addNode(nodeMalloc(COS_G));
}
void MainWindow::on_actionMin_triggered(){
	addNode(nodeMalloc(MIN_G));
}
void MainWindow::on_actionMax_triggered(){
	addNode(nodeMalloc(MAX_G));
}
void MainWindow::on_actionRatio_triggered(){
	addNode(nodeMalloc(RATIO_G));
}
void MainWindow::on_actionComplex_triggered(){
	addNode(nodeMalloc(CPLX_G));
}
void MainWindow::on_actionHSV_triggered(){
	addNode(nodeMalloc(HSV_G));
}
void MainWindow::on_actionRGB_triggered(){
	addNode(nodeMalloc(RGB_G));
}
