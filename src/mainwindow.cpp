#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow){
	ui->setupUi(this);
	QWidget::setWindowTitle("Emergence");
	QWidget::setWindowIcon(QIcon(":/icons/emgc.ico"));

	scene=ui->workspace->scene();

	connect(ui->actionCopy,SIGNAL(triggered(bool)),ui->workspace,SLOT(copy()));
	connect(ui->actionPaste,SIGNAL(triggered(bool)),ui->workspace,SLOT(paste()));
	connect(ui->actionCut,SIGNAL(triggered(bool)),ui->workspace,SLOT(cut()));
	connect(ui->actionDelete,SIGNAL(triggered(bool)),ui->workspace,SLOT(delete_selected()));
	connect(ui->actionSelect_all,SIGNAL(triggered(bool)),ui->workspace,SLOT(select_all()));

	connect(ui->actionSave_as,SIGNAL(triggered(bool)),this,SLOT(save()));
	connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(load()));

	connect(ui->actionUndo,SIGNAL(triggered(bool)),&ui->workspace->undoStack,SLOT(undo()));
	connect(ui->actionRedo,SIGNAL(triggered(bool)),&ui->workspace->undoStack,SLOT(redo()));
	ui->actionUndo->setEnabled(false); ui->actionRedo->setEnabled(false);
	connect(&ui->workspace->undoStack,SIGNAL(canUndoChanged(bool)),ui->actionUndo,SLOT(setEnabled(bool)));
	connect(&ui->workspace->undoStack,SIGNAL(canRedoChanged(bool)),ui->actionRedo,SLOT(setEnabled(bool)));

	connect(scene,SIGNAL(selectionChanged()),this,SLOT(updateActions()));
}
MainWindow::~MainWindow(){
	delete ui->workspace;
	delete ui;
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

	ui->workspace->select_all();
	out << Node::nodesToBin(scene->selectedItems());
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

	ui->workspace->select_all();
	ui->workspace->undoStack.beginMacro("load");
	ui->workspace->delete_selected();
	ui->workspace->addNodes(Node::binToNodes(file.readAll()));
	ui->workspace->undoStack.endMacro();
	scene->clearSelection();
}

void MainWindow::on_actionExit_triggered(){
	close();
}
void MainWindow::updateActions(){
	ui->actionExport->setEnabled(false);
	for(auto& n: scene->selectedItems())
		if(((Node*)n)->id==Node::RENDER_G && *((RenderNode*)n)){
			ui->actionExport->setEnabled(true);
			break;
		}
}
void MainWindow::on_actionExport_triggered(){
	for(const auto& n: scene->selectedItems())
		if(((Node*)n)->id==Node::RENDER_G && *((RenderNode*)n))
			ExportImageDialog::exportBMP((RenderNode*)n);
}
void MainWindow::on_actionIf_triggered(){
	ui->workspace->addNode(Node::IF_G);
}
void MainWindow::on_actionGreaterThan_triggered(){
	ui->workspace->addNode(Node::GT_G);
}
void MainWindow::on_actionLessThan_triggered(){
	ui->workspace->addNode(Node::LT_G);
}
void MainWindow::on_actionEqual_triggered(){
	ui->workspace->addNode(Node::EQ_G);
}
void MainWindow::on_actionNot_Equal_triggered(){
	ui->workspace->addNode(Node::NE_G);
}
void MainWindow::on_actionAND_triggered(){
	ui->workspace->addNode(Node::AND_G);
}
void MainWindow::on_actionOR_triggered(){
	ui->workspace->addNode(Node::OR_G);
}
void MainWindow::on_actionXOR_triggered(){
	ui->workspace->addNode(Node::XOR_G);
}
void MainWindow::on_actionNOT_triggered(){
	ui->workspace->addNode(Node::NOT_G);
}
void MainWindow::on_actionDouble_triggered(){
	ui->workspace->addNode(Node::DOUBLE_G);
}
void MainWindow::on_actionColor_triggered(){
	ui->workspace->addNode(Node::COLOR_G);
}
void MainWindow::on_actionLUT_triggered(){
	ui->workspace->addNode(Node::PALETTE_G);
}
void MainWindow::on_actionX_triggered(){
	ui->workspace->addNode(Node::X_G);
}
void MainWindow::on_actionY_triggered(){
	ui->workspace->addNode(Node::Y_G);
}
void MainWindow::on_actionRender_triggered(){
	ui->workspace->addNode(Node::RENDER_G);
}
void MainWindow::on_actionADD_triggered(){
	ui->workspace->addNode(Node::ADD_G);
}
void MainWindow::on_actionSUB_triggered(){
	ui->workspace->addNode(Node::SUB_G);
}
void MainWindow::on_actionMUL_triggered(){
	ui->workspace->addNode(Node::MUL_G);
}
void MainWindow::on_actionDIV_triggered(){
	ui->workspace->addNode(Node::DIV_G);
}
void MainWindow::on_actionNEG_triggered(){
	ui->workspace->addNode(Node::NEG_G);
}
void MainWindow::on_actionSQRT_triggered(){
	ui->workspace->addNode(Node::SQRT_G);
}
void MainWindow::on_actionABS_triggered(){
	ui->workspace->addNode(Node::ABS_G);
}
void MainWindow::on_actionLerp_triggered(){
	ui->workspace->addNode(Node::LERP_G);
}
void MainWindow::on_actionClamp_triggered(){
	ui->workspace->addNode(Node::CLAMP_G);
}
void MainWindow::on_actionBitmap_triggered(){
	ui->workspace->addNode(Node::BITMAP_G);
}
void MainWindow::on_actionSin_triggered(){
	ui->workspace->addNode(Node::SIN_G);
}
void MainWindow::on_actionCos_triggered(){
	ui->workspace->addNode(Node::COS_G);
}
void MainWindow::on_actionMin_triggered(){
	ui->workspace->addNode(Node::MIN_G);
}
void MainWindow::on_actionMax_triggered(){
	ui->workspace->addNode(Node::MAX_G);
}
void MainWindow::on_actionRatio_triggered(){
	ui->workspace->addNode(Node::RATIO_G);
}
void MainWindow::on_actionComplex_triggered(){
	ui->workspace->addNode(Node::CPLX_G);
}
void MainWindow::on_actionHSV_triggered(){
	ui->workspace->addNode(Node::HSV_G);
}
void MainWindow::on_actionRGB_triggered(){
	ui->workspace->addNode(Node::RGB_G);
}
void MainWindow::on_actionFunction_Manager_triggered(){
	fm.exec();
}
