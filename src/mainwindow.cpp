#include "mainwindow.h"
#include "ui_mainwindow.h"

const int MainWindow::_magic_number;
const int MainWindow::_version;
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow){
	ui->setupUi(this);
	QWidget::setWindowTitle("Emergence");
	QWidget::setWindowIcon(QIcon(":/icons/emgc.ico"));

	ui->workspace->setScene(scene=new Workspace);
	ui->workspace->setAcceptDrops(true);
	ui->workspace->setDragMode(QGraphicsView::DragMode::RubberBandDrag);
	scene->putXYandOutput();

	scene->undoStack.setClean();
	connect(ui->actionCopy,SIGNAL(triggered(bool)),scene,SLOT(copy()));
	connect(ui->actionPaste,SIGNAL(triggered(bool)),scene,SLOT(paste()));
	connect(ui->actionCut,SIGNAL(triggered(bool)),scene,SLOT(cut()));
	connect(ui->actionDelete,SIGNAL(triggered(bool)),scene,SLOT(delete_selected()));
	connect(ui->actionSelect_all,SIGNAL(triggered(bool)),scene,SLOT(select_all()));

	connect(ui->actionSave_as,SIGNAL(triggered(bool)),this,SLOT(save()));
	connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(load()));

	connect(ui->actionUndo,SIGNAL(triggered(bool)),&scene->undoStack,SLOT(undo()));
	connect(ui->actionRedo,SIGNAL(triggered(bool)),&scene->undoStack,SLOT(redo()));
	ui->actionUndo->setEnabled(false); ui->actionRedo->setEnabled(false);
	connect(&scene->undoStack,SIGNAL(canUndoChanged(bool)),ui->actionUndo,SLOT(setEnabled(bool)));
	connect(&scene->undoStack,SIGNAL(canRedoChanged(bool)),ui->actionRedo,SLOT(setEnabled(bool)));

	connect(scene,SIGNAL(selectionChanged()),this,SLOT(updateActions()));
	updateActions();
	ui->actionPaste->setEnabled(QApplication::clipboard()->mimeData()->text()=="Emergence_Nodes");
	zoomIN.setShortcut(QKeySequence::ZoomIn);
	zoomOUT.setShortcut(QKeySequence::ZoomOut);
	addAction(&zoomIN);
	addAction(&zoomOUT);
	connect(&zoomIN,SIGNAL(triggered(bool)),this,SLOT(zoomIn()));
	connect(&zoomOUT,SIGNAL(triggered(bool)),this,SLOT(zoomOut()));
}
MainWindow::~MainWindow(){
	delete ui->workspace;
	delete ui;
}
void MainWindow::zoomIn()const{
	ui->workspace->scale(Workspace::scaleFactor,Workspace::scaleFactor);
}
void MainWindow::zoomOut()const{
	ui->workspace->scale(1/Workspace::scaleFactor,1/Workspace::scaleFactor);
}
void MainWindow::save()const{
//	QString fileName= QFileDialog::getSaveFileName(ui->workspace,"Save as...",".","Node Files (*.emrg)");
//	if(fileName.isEmpty()) return;
//	if(!fileName.endsWith(".emrg"))
//		fileName.append(".emrg");
//	QFile file(fileName);
//	if(!file.open(QIODevice::WriteOnly)){
//		QMessageBox::information(ui->workspace,"Unable to open file",file.errorString());
//		return;
//	}
//	file.resize(0);
//	QDataStream out(&file);

//	out << MAGIC_NUMBER;
//	out << SAVE_VERSION;

//	scene->select_all();
//	out << Node::nodesToBin(scene->selectedItems());
//	scene->clearSelection();
//	file.close();
	std::ofstream ofs("test.bin");
	ofs.write(reinterpret_cast<const char*>(&_magic_number),4);
	ofs.write(reinterpret_cast<const char*>(&_version),4);
	int tmp= FunctionManager::count();
	ofs << tmp << '\n';
	for(int i=0; i<tmp;i++)
		ofs<<*FunctionManager::functionAt(i);
	ofs << *scene;
	ofs.close();
}

void MainWindow::load(){
//	QString f= QFileDialog::getOpenFileName(parentWidget(),"Open File",".","Node Files (*.emrg)");
//	if(f.isNull()) return;
//	QFile file(f);
//	file.open(QIODevice::ReadOnly);
//	QDataStream in(&file);
//	int magic; in>>magic;
//	uint version; in>>version;
//	in.skipRawData(4);

//	scene->select_all();
//	scene->undoStack.beginMacro("load");
//	scene->delete_selected();
//	scene->addNodes(Node::binToNodes(file.readAll()));
//	scene->undoStack.endMacro();
//	scene->clearSelection();
	std::ifstream ifs("test.bin");
	int tmp;
	ifs.read(reinterpret_cast<char*>(&tmp),4);
	if(tmp!=_magic_number){
		QMessageBox::warning(0,"Wrong format","Bad File Format");
		ifs.close();
		return;
	}
	ifs.read(reinterpret_cast<char*>(&tmp),4);
	if(tmp<_version){
		QMessageBox::warning(0,"Wrong version","Sorry, this save file is too old.");
		ifs.close();
		return;
	}
//	fm.clear();
	ifs>>tmp;
	for(int i=0;i<tmp;i++)
		ifs >> fm;
	ifs >> *scene;
	ifs.close();
}

void MainWindow::on_actionExit_triggered(){
	close();
}
void MainWindow::updateActions(){
	ui->actionExport->setEnabled(false);
	bool someNodeIsSelected=false;
	for(auto& n: scene->selectedItems()){
		if(((Node*)n)->id!=Node::OUTPUT_G &&((Node*)n)->id!=Node::INPUT_G)
			someNodeIsSelected=true;
		if(((Node*)n)->id==Node::RENDER_G && *((RenderNode*)n)){
			ui->actionExport->setEnabled(true);
			break;
		}
	}
	ui->actionCut->setEnabled(someNodeIsSelected);
	ui->actionCopy->setEnabled(someNodeIsSelected);
	ui->actionDelete->setEnabled(someNodeIsSelected);
}
void MainWindow::on_actionExport_triggered(){
	for(const auto& n: scene->selectedItems())
		if(((Node*)n)->id==Node::RENDER_G && *((RenderNode*)n))
			ExportImageDialog::exportBMP((RenderNode*)n);
}
void MainWindow::on_actionIf_triggered(){
	scene->addNode(Node::nodeMalloc(Node::IF_G));
}
void MainWindow::on_actionGreaterThan_triggered(){
	scene->addNode(Node::nodeMalloc(Node::GT_G));
}
void MainWindow::on_actionLessThan_triggered(){
	scene->addNode(Node::nodeMalloc(Node::LT_G));
}
void MainWindow::on_actionEqual_triggered(){
	scene->addNode(Node::nodeMalloc(Node::EQ_G));
}
void MainWindow::on_actionNot_Equal_triggered(){
	scene->addNode(Node::nodeMalloc(Node::NE_G));
}
void MainWindow::on_actionAND_triggered(){
	scene->addNode(Node::nodeMalloc(Node::AND_G));
}
void MainWindow::on_actionOR_triggered(){
	scene->addNode(Node::nodeMalloc(Node::OR_G));
}
void MainWindow::on_actionXOR_triggered(){
	scene->addNode(Node::nodeMalloc(Node::XOR_G));
}
void MainWindow::on_actionNOT_triggered(){
	scene->addNode(Node::nodeMalloc(Node::NOT_G));
}
void MainWindow::on_actionDouble_triggered(){
	scene->addNode(Node::nodeMalloc(Node::DOUBLE_G));
}
void MainWindow::on_actionColor_triggered(){
	scene->addNode(Node::nodeMalloc(Node::COLOR_G));
}
void MainWindow::on_actionLUT_triggered(){
	scene->addNode(Node::nodeMalloc(Node::PALETTE_G));
}
void MainWindow::on_actionX_triggered(){
	scene->addNode(Node::nodeMalloc(Node::X_G));
}
void MainWindow::on_actionY_triggered(){
	scene->addNode(Node::nodeMalloc(Node::Y_G));
}
void MainWindow::on_actionRender_triggered(){
	scene->addNode(Node::nodeMalloc(Node::RENDER_G));
}
void MainWindow::on_actionADD_triggered(){
	scene->addNode(Node::nodeMalloc(Node::ADD_G));
}
void MainWindow::on_actionSUB_triggered(){
	scene->addNode(Node::nodeMalloc(Node::SUB_G));
}
void MainWindow::on_actionMUL_triggered(){
	scene->addNode(Node::nodeMalloc(Node::MUL_G));
}
void MainWindow::on_actionDIV_triggered(){
	scene->addNode(Node::nodeMalloc(Node::DIV_G));
}
void MainWindow::on_actionNEG_triggered(){
	scene->addNode(Node::nodeMalloc(Node::NEG_G));
}
void MainWindow::on_actionSQRT_triggered(){
	scene->addNode(Node::nodeMalloc(Node::SQRT_G));
}
void MainWindow::on_actionABS_triggered(){
	scene->addNode(Node::nodeMalloc(Node::ABS_G));
}
void MainWindow::on_actionLerp_triggered(){
	scene->addNode(Node::nodeMalloc(Node::LERP_G));
}
void MainWindow::on_actionClamp_triggered(){
	scene->addNode(Node::nodeMalloc(Node::CLAMP_G));
}
void MainWindow::on_actionBitmap_triggered(){
	scene->addNode(Node::nodeMalloc(Node::BITMAP_G));
}
void MainWindow::on_actionSin_triggered(){
	scene->addNode(Node::nodeMalloc(Node::SIN_G));
}
void MainWindow::on_actionCos_triggered(){
	scene->addNode(Node::nodeMalloc(Node::COS_G));
}
void MainWindow::on_actionMin_triggered(){
	scene->addNode(Node::nodeMalloc(Node::MIN_G));
}
void MainWindow::on_actionMax_triggered(){
	scene->addNode(Node::nodeMalloc(Node::MAX_G));
}
void MainWindow::on_actionRatio_triggered(){
	scene->addNode(Node::nodeMalloc(Node::RATIO_G));
}
void MainWindow::on_actionComplex_triggered(){
	scene->addNode(Node::nodeMalloc(Node::CPLX_G));
}
void MainWindow::on_actionHSV_triggered(){
	scene->addNode(Node::nodeMalloc(Node::HSV_G));
}
void MainWindow::on_actionRGB_triggered(){
	scene->addNode(Node::nodeMalloc(Node::RGB_G));
}
void MainWindow::on_actionFunction_Manager_triggered(){
	fm.exec();
}
void MainWindow::on_actionFunction_triggered(){
	Function* f= FunctionManager::getFunction();
	if(f) scene->addNode(Node::nodeMalloc(Node::FUNC_G,f));
}
