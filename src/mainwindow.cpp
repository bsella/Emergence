#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>
#include <QFileDialog>

const int MainWindow::_magic_number;
const int MainWindow::_version;
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow){

	ui->setupUi(this);

	QWidget::setWindowTitle("Emergence");
	QWidget::setWindowIcon(QIcon(":/emgc.ico"));

	ui->workspace->setScene(scene=new Workspace);
	ui->workspace->setAcceptDrops(true);
	ui->workspace->setDragMode(QGraphicsView::DragMode::RubberBandDrag);

	connect(ui->actionCopy,SIGNAL(triggered(bool)),scene,SLOT(copy()));
	connect(ui->actionPaste,SIGNAL(triggered(bool)),scene,SLOT(paste()));
	connect(ui->actionCut,SIGNAL(triggered(bool)),scene,SLOT(cut()));
	connect(ui->actionDelete,SIGNAL(triggered(bool)),scene,SLOT(delete_selected()));
	connect(ui->actionSelect_all,SIGNAL(triggered(bool)),scene,SLOT(select_all()));

	connect(ui->actionUndo,SIGNAL(triggered(bool)),&scene->undoStack,SLOT(undo()));
	connect(ui->actionRedo,SIGNAL(triggered(bool)),&scene->undoStack,SLOT(redo()));
	ui->actionUndo->setEnabled(false); ui->actionRedo->setEnabled(false);
	connect(&scene->undoStack,SIGNAL(canUndoChanged(bool)),ui->actionUndo,SLOT(setEnabled(bool)));
	connect(&scene->undoStack,SIGNAL(canRedoChanged(bool)),ui->actionRedo,SLOT(setEnabled(bool)));

//	connect(scene,SIGNAL(selectionChanged()),this,SLOT(updateActions()));
//	updateActions();
//	ui->actionPaste->setEnabled(QApplication::clipboard()->mimeData()->text()=="Emergence_Nodes");
//	connect(ui->actionCopy,SIGNAL(triggered(bool)),ui->actionPaste,SLOT(setDisabled(bool)));
	zoomIN.setShortcut(QKeySequence::ZoomIn);
	zoomOUT.setShortcut(QKeySequence::ZoomOut);
	connect(&zoomIN,SIGNAL(triggered(bool)),this,SLOT(zoomIn()));
	connect(&zoomOUT,SIGNAL(triggered(bool)),this,SLOT(zoomOut()));
	addAction(&zoomIN);
	addAction(&zoomOUT);
	pluginManager= new PluginManager(ui);
	if(!pluginManager->loadPlugins()){
		ui->menuInsert->setEnabled(false);
		delete ui->toolboxDock;
	}
	connect(&scene->undoStack,SIGNAL(indexChanged(int)),this,SLOT(updateModified()));
	connect(&scene->undoStack,SIGNAL(cleanChanged(bool)),this,SLOT(updateModified()));
}

MainWindow::~MainWindow(){
	delete ui;
}
void MainWindow::zoomIn()const{
	ui->workspace->scale(Workspace::scaleFactor,Workspace::scaleFactor);
}
void MainWindow::zoomOut()const{
	ui->workspace->scale(1/Workspace::scaleFactor,1/Workspace::scaleFactor);
}

bool MainWindow::on_actionSave_triggered(){
	if(_filePath=="<untitled>")
		return on_actionSave_as_triggered();
	std::ofstream ofs(_filePath.toStdString());

	ofs.write(reinterpret_cast<const char*>(&_magic_number),4);
	ofs.write(reinterpret_cast<const char*>(&_version),4);

	pluginManager->save(ofs);

	ofs << *scene;
	ofs.close();
	scene->undoStack.setClean();
	return true;
}
bool MainWindow::on_actionSave_as_triggered(){
	QString fileName= QFileDialog::getSaveFileName(ui->workspace,"Save as...",".","Node Files (*.emrg)");
	if(fileName.isEmpty()) return false;
	if(!fileName.endsWith(".emrg"))
		fileName.append(".emrg");
	_filePath=fileName;
	return on_actionSave_triggered();
}
void MainWindow::on_actionOpen_triggered(){
	QString fileName= QFileDialog::getOpenFileName(parentWidget(),"Open File",".","Node Files (*.emrg)");
	if(fileName.isNull()) return;

	switch (areYouSure()) {
		case QMessageBox::Yes:
			if(!on_actionSave_triggered()) return;
			break;
		case QMessageBox::No:break;
		case QMessageBox::Cancel:return;
		default:break;
	}

	std::ifstream ifs(fileName.toStdString());
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
	pluginManager->load(ifs);

	scene->select_all();
	scene->undoStack.beginMacro("load");
	scene->delete_selected();
	ifs >> *scene;
	scene->undoStack.endMacro();
	scene->clearSelection();
	ifs.close();
	_filePath=fileName;
	scene->undoStack.setClean();
}

void MainWindow::updateModified(){
	fileModified=!scene->undoStack.isClean();
	QString title = "Emergence";
	if(_filePath!="<untitled>")
		title+=" - "+_filePath.split('/').back();
	if(fileModified)
		title+="*";
	setWindowTitle(title);
}

void MainWindow::on_actionNew_triggered(){
	switch (areYouSure()) {
		case QMessageBox::Yes:
			if(!on_actionSave_triggered()) return;
			break;
		case QMessageBox::No:break;
		case QMessageBox::Cancel:return;
		default:break;
	}
	scene->undoStack.clear();
	scene->undoStack.setClean();
	_filePath="<untitled>";
	updateModified();
}

void MainWindow::on_actionExit_triggered(){
	close();
}
int MainWindow::areYouSure(){
	if(fileModified){
		return QMessageBox::question(this,"Save changes",
			"Save changes to "+_filePath+" before closing?",
			(QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel));
	}
	return QMessageBox::No;
}
void MainWindow::closeEvent(QCloseEvent*event){
	switch (areYouSure()){
		case QMessageBox::Yes:
			if(!on_actionSave_triggered())
				event->ignore();
			break;
		case QMessageBox::No:break;
		case QMessageBox::Cancel:
			event->ignore();
			break;
		default:
			break;
	}
}
//void MainWindow::updateActions(){
//	ui->actionExport->setEnabled(false);
//	bool someNodeIsSelected=false;
//	for(auto& n: scene->selectedItems()){
//		if(((Node*)n)->id!=Node::OUTPUT_G &&((Node*)n)->id!=Node::INPUT_G)
//			someNodeIsSelected=true;
//		if(((Node*)n)->id==Node::RENDER_G){
//			ui->actionExport->setEnabled(true);
//			break;
//		}
//	}
//	ui->actionCut->setEnabled(someNodeIsSelected);
//	ui->actionCopy->setEnabled(someNodeIsSelected);
//	ui->actionDelete->setEnabled(someNodeIsSelected);
//}
