#include "include/Workspace.h"

Workspace::Workspace(QWidget *parent):QGraphicsView(parent),scene(new QGraphicsScene){
	setScene(scene);
	setAcceptDrops(true);
	setDragMode(DragMode::RubberBandDrag);
}

void Workspace::setRA(RenderArea* ra){
	if (!ra) return;
	renderArea=ra;
	addNode(X_G,{0,0});
	addNode(Y_G,{0,100});
	addNode(RENDER_G,{100,50});
}

Node* Workspace::addNode(uint g, bool load){
	return addNode(g, scene->sceneRect().center(), load);
}

Node* Workspace::addNode(uint g, const QPointF& pos, bool load){
	Node* node;
	switch(g){
	case DOUBLE_G:{
		if(load){
			node=new ConstNode(0.0);
			break;
		}
		bool ok;
		double d =QInputDialog::getDouble(this,"Choose Number","",0,-2147483647,2147483647,3,&ok);
		if(!ok) return nullptr;
		node=new ConstNode(d);
		break;
	}
	case COLOR_G:{
		if(load){
			node=new ConstNode(0xffffffff);
			break;
		}
		QColor c =QColorDialog::getColor(Qt::white,this);
		if(!c.isValid()) return nullptr;
		node=new ConstNode(c.rgba());
		break;
	}
	case PALETTE_G:{
		///TODO : Implement dialog for palette
		Palette p;
		p.add(0xffff0000,0);
		p.add(0xff0000ff,.5);
		p.add(0xff00ff00,1);
		node= new LUTNode(p);
		break;
	}
	case BITMAP_G:{
		if(load){
			node=new BitmapNode;
			break;
		}
		QString f= QFileDialog::getOpenFileName(this,"Choose Image",".","Images (*.bmp)");
		if(f.isNull())return nullptr;
		node = new BitmapNode(f);
		break;
	}
	case IF_G:		node=new IfNode;break;
	case GT_G:		node=new GTNode;break;
	case LT_G:		node=new LTNode;break;
	case EQ_G:		node=new EQNode;break;
	case NE_G:		node=new NENode;break;
	case OR_G:		node=new ORNode;break;
	case AND_G:		node=new ANDNode;break;
	case XOR_G:		node=new XORNode;break;
	case NOT_G:		node=new NOTNode;break;
	case X_G:
		if(!renderArea) return nullptr;
		node=renderArea->xg;
		break;
	case Y_G:
		if(!renderArea) return nullptr;
		node= renderArea->yg;
		break;
	case RENDER_G:
		if(!renderArea) return nullptr;
		node=renderArea->start;
		break;
	case RATIO_G:
		if(!renderArea) return nullptr;
		node=renderArea->ratio;
		break;
	case ADD_G:		node=new ADDNode;break;
	case SUB_G:		node=new SUBNode;break;
	case MUL_G:		node=new MULNode;break;
	case DIV_G:		node=new DIVNode;break;
	case NEG_G:		node=new NEGNode;break;
	case SQRT_G:	node=new SQRTNode;break;
	case ABS_G:		node=new ABSNode;break;
	case LERP_G:	node=new LERPNode;break;
	case CLAMP_G:	node=new CLAMPNode;break;
	case SIN_G:		node=new SINNode;break;
	case COS_G:		node=new COSNode;break;
	case MIN_G:		node=new MINNode;break;
	case MAX_G:		node=new MAXNode;break;
	case RGB_G:		node=new RGBNode;break;
	case HSV_G:		node=new HSVNode;break;
	case CPLX_G:	node=new ComplexNode;break;
	default:return nullptr;
	}
	connect(node,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	connect(node,SIGNAL(removeFromWS(Node*)),this,SLOT(removeFromList(Node*)));
	connect(scene,SIGNAL(selectionChanged()),node,SLOT(updateSelection()));
	if(load) node->setPos(pos);
	else node->setPos(pos-node->boundingRect().center());
	Nodes.push_back(node);
	if(!scene->items().contains(node))
		scene->addItem(node);
	node->setZValue(0);
	for(const auto& i: node->collidingItems())
		if(node->zValue()<= i->zValue())
			node->setZValue(i->zValue()+1);
	return node;
}

void Workspace::removeFromList(Node *g){
	Nodes.removeOne(g);
}

void Workspace::clear(){
	while(!Nodes.empty())
		Nodes.back()->removeNode();
}

QByteArray Workspace::nodesToText(const QList<Node *> &nodes) const{
	QByteArray ret;
	QDataStream ds (&ret,QIODevice::Append);
	ds<<nodes.size();
	for(const auto& n:nodes){
		ds<<n->id;
		ds<<n->scenePos().x();
		ds<<n->scenePos().y();
		if(n->id==DOUBLE_G)
			ds<<n->val.d;
		else if(n->id==COLOR_G)
			ds<<n->val.clr;
	}
	for(const auto& n : nodes)
		for(const auto& nn: n->iNodes)
			ds<<nodes.indexOf(nn);
	return ret;
}

void Workspace::textToNodes(const QByteArray &ba){
	QDataStream ds(ba);
	int n; ds>>n;
	int id; float x,y;
	QList<Node*> newNodes;
	for(int i=0; i<n; i++){
		ds>>id;
		ds>>x;
		ds>>y;
		Node* newNode = addNode(id,QPointF(x,y),true);
		if(id==DOUBLE_G)
			ds>>newNode->val.d;
		else if(id==COLOR_G){
			ds>>newNode->val.clr;
			newNode->color=newNode->val.clr;
		}
		newNodes.append(newNode);
	}
	for(auto& node: newNodes)
		for(unsigned i=0; i<node->nbArgs; i++){
			ds>>n;
			if(n>=0)
				node->sockets[i]->connectToNode(newNodes.at(n));
		}
	for(auto& n:scene->selectedItems())
		n->setSelected(false);
	for(const auto& n:newNodes)
		n->setSelected(true);
}

void Workspace::save()const{
	QString f= QFileDialog::getSaveFileName(parentWidget(),"Save as...",".","Node Files (*.emrg)");
	if(f.isNull()) return;
	if(!f.endsWith(".emrg"))
		f.append(".emrg");
	QFile file(f);
	file.open(QIODevice::WriteOnly);
	file.resize(0);
	QDataStream out(&file);

	out << MAGIC_NUMBER;
	out << SAVE_VERSION;

	out << nodesToText(Nodes);
}

void Workspace::load(){
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
	clear();
	in.skipRawData(4);
	textToNodes(file.readAll());
	for(auto& n:scene->selectedItems())
		n->setSelected(false);
}

Workspace::~Workspace(){
	clear();
	delete scene;
	delete renderArea;
}

void Workspace::dragEnterEvent(QDragEnterEvent *event){
	event->setAccepted(event->mimeData()->text()=="nodeTool");
	QGraphicsView::dragEnterEvent(event);
}

void Workspace::dropEvent(QDropEvent *event){
	addNode(event->mimeData()->data("type").toInt(),
				mapToScene(event->pos()));
}

void Workspace::dragMoveEvent(QDragMoveEvent *){}

QList<Node*> Workspace::selectedNodes()const{
	QList<Node*> ret;
	for(const auto& n: scene->selectedItems())
		ret.append((Node*)n);
	return ret;
}

void Workspace::copy()const{
	QMimeData * mime=new QMimeData;
	mime->setText("Emergence_Nodes");
	mime->setData("copy",nodesToText(selectedNodes()));
	QApplication::clipboard()->setMimeData(mime);
}

void Workspace::cut(){
	copy();
	delete_selected();
}

void Workspace::paste(){
	const QMimeData* mime= QApplication::clipboard()->mimeData();
	if(mime->text()=="Emergence_Nodes")
		textToNodes(mime->data("copy"));
}

void Workspace::select_all(){
	for(auto& n : Nodes)
		n->setSelected(true);
}

void Workspace::delete_selected(){
	for(auto& n : scene->selectedItems())
		((Node*)n)->removeNode();
}
