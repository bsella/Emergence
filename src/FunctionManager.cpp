#include "headers/FunctionManager.h"
#include "ui_functionmanager.h"

FunctionManager* FunctionManager::singleton;

FunctionManager::FunctionManager(QWidget *parent):
	QDialog(parent), ui(new Ui::FunctionManager){
	ui->setupUi(this);
	singleton=this;
	ui->workspace->setAcceptDrops(true);
	ui->workspace->setDragMode(QGraphicsView::DragMode::RubberBandDrag);
	undoStack.push(new AddFunctionCommand);
	setFunction((Function*)ui->listWidget->item(0));
	undoStack.setClean();
	ui->removeFunctionButton->setEnabled(false);
	ui->listWidget->setItemSelected(ui->listWidget->item(0),true);
	connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(renameFunction(QListWidgetItem*)));
	connect(ui->listWidget,&QListWidget::currentItemChanged,this,&FunctionManager::setFunction);
	connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
	connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(reject()));

	del.setShortcut(QKeySequence::Delete);
	copy.setShortcut(QKeySequence::Copy);
	cut.setShortcut(QKeySequence::Cut);
	paste.setShortcut(QKeySequence::Paste);
	select_all.setShortcut(QKeySequence::SelectAll);
	undo.setShortcut(QKeySequence::Undo);
	redo.setShortcut(QKeySequence::Redo);
	addAction(&undo);
	addAction(&redo);
	addAction(&select_all);
	addAction(&paste);
	addAction(&cut);
	addAction(&copy);
	addAction(&del);
}

void FunctionManager::accept(){
	undoStack.setClean();
	for(int i=0; i<ui->listWidget->count();i++)
		((Function*)ui->listWidget->item(i))->scene->undoStack.setClean();
	QDialog::accept();
}
void FunctionManager::reject(){
	while(!undoStack.isClean())
		undoStack.undo();
	for(int i=0; i<ui->listWidget->count();i++){
		Function *f=(Function*)ui->listWidget->item(i);
		while(!f->scene->undoStack.isClean())
			f->scene->undoStack.undo();
	}
	QDialog::reject();
}

FunctionManager::~FunctionManager(){
	delete ui;
}

void FunctionManager::on_addFunctionButton_clicked(){
	undoStack.push(new AddFunctionCommand);
}
void FunctionManager::on_removeFunctionButton_clicked(){
	undoStack.push(new RemoveFunctionCommand);
}
void FunctionManager::renameFunction(QListWidgetItem *item){
	QString newname= QInputDialog::getText(this,"Change function name", "Name :");
	if(!newname.isNull())
		undoStack.push(new RenameFunctionCommand((Function*)item,newname));
}

Function* FunctionManager::getFunction(FunctionNode *node){
	if(node) singleton->ui->listWidget->setCurrentItem(node->func);
	if(singleton->exec())
		return (Function*)singleton->ui->listWidget->currentItem();
	return nullptr;
}

void FunctionManager::addNewFunction()const{
	Function* func= new Function;
	ui->listWidget->addItem(func);
	ui->listWidget->setCurrentItem(func);
	connect(func->start,SIGNAL(connected(Node::Socket*,Node*)),func->scene,SLOT(connectNode(Node::Socket*,Node*)));
	connect(func->start,SIGNAL(disconnected(Node::Socket*)),func->scene,SLOT(disconnectNode(Node::Socket*)));
	for(Node* n:func->iNodes){
		connect(n,SIGNAL(connected(Node::Socket*,Node*)),func->scene,SLOT(connectNode(Node::Socket*,Node*)));
		connect(n,SIGNAL(disconnected(Node::Socket*)),func->scene,SLOT(disconnectNode(Node::Socket*)));
	}
	ui->removeFunctionButton->setEnabled(true);
}

bool FunctionManager::userIntented=true;

void FunctionManager::on_spinBox_valueChanged(int arg1){
	if(userIntented)
		func->scene->undoStack.push(new ChangeNbArgsCommand(func,func->nbArgs,arg1));
}

void FunctionManager::setFunction(QListWidgetItem* f){
	if(func){
		disconnect(&redo,SIGNAL(triggered(bool)),&func->scene->undoStack,SLOT(redo()));
		disconnect(&undo,SIGNAL(triggered(bool)),&func->scene->undoStack,SLOT(undo()));
		disconnect(&select_all,SIGNAL(triggered(bool)),func->scene,SLOT(select_all()));
		disconnect(&paste,SIGNAL(triggered(bool)),func->scene,SLOT(paste()));
		disconnect(&cut,SIGNAL(triggered(bool)),func->scene,SLOT(cut()));
		disconnect(&copy,SIGNAL(triggered(bool)),func->scene,SLOT(copy()));
		disconnect(&del,SIGNAL(triggered(bool)),func->scene,SLOT(delete_selected()));
	}
	func=(Function*)f;
	ui->workspace->setScene(func->scene);
	userIntented=false;
	ui->spinBox->setValue(func->nbArgs);
	userIntented=true;
	connect(&del,SIGNAL(triggered(bool)),func->scene,SLOT(delete_selected()));
	connect(&copy,SIGNAL(triggered(bool)),func->scene,SLOT(copy()));
	connect(&cut,SIGNAL(triggered(bool)),func->scene,SLOT(cut()));
	connect(&paste,SIGNAL(triggered(bool)),func->scene,SLOT(paste()));
	connect(&select_all,SIGNAL(triggered(bool)),func->scene,SLOT(select_all()));
	connect(&undo,SIGNAL(triggered(bool)),&func->scene->undoStack,SLOT(undo()));
	connect(&redo,SIGNAL(triggered(bool)),&func->scene->undoStack,SLOT(redo()));
}

ChangeNbArgsCommand::ChangeNbArgsCommand(Function* f,int from, int to,QUndoCommand* parent)
	:QUndoCommand(parent){
	_from=from;
	_to=to;
	func=f;
}
void ChangeNbArgsCommand::undo(){
	if(_to>_from)
		for(int i=_from; i<_to; i++){
			func->scene->removeItem(func->iNodes[i]);
			delete func->iNodes[i];
			func->iNodes.pop_back();
		}
	else
		for(int i=_to; i<_from; i++){
			func->iNodes.push_back(new Function::InputNode(i));
			func->scene->addItem(func->iNodes[i]);
		}
	func->nbArgs=_from;
	FunctionManager::userIntented=false;
	FunctionManager::singleton->ui->spinBox->setValue(_from);
	FunctionManager::userIntented=true;
	func->scene->update();
}
void ChangeNbArgsCommand::redo(){
	if(_to>_from)
		for(int i=_from; i<_to; i++){
			func->iNodes.push_back(new Function::InputNode(i));
			func->scene->addItem(func->iNodes[i]);
		}
	else
		for(int i=_to; i<_from; i++){
			func->scene->removeItem(func->iNodes[i]);
			delete func->iNodes[i];
			func->iNodes.pop_back();
		}
	func->nbArgs=_to;
	FunctionManager::userIntented=false;
	FunctionManager::singleton->ui->spinBox->setValue(_to);
	FunctionManager::userIntented=true;
	func->scene->update();
}

AddFunctionCommand::AddFunctionCommand(QUndoCommand*parent)
	:QUndoCommand(parent){
	func= new Function;
}
void AddFunctionCommand::undo(){
	QObject::disconnect(func->start,SIGNAL(disconnected(Node::Socket*)),func->scene,SLOT(disconnectNode(Node::Socket*)));
	QObject::disconnect(func->start,SIGNAL(connected(Node::Socket*,Node*)),func->scene,SLOT(connectNode(Node::Socket*,Node*)));
	for(Node* n:func->iNodes){
		QObject::disconnect(n,SIGNAL(connected(Node::Socket*,Node*)),func->scene,SLOT(connectNode(Node::Socket*,Node*)));
		QObject::disconnect(n,SIGNAL(disconnected(Node::Socket*)),func->scene,SLOT(disconnectNode(Node::Socket*)));
	}
	delete func;
	FunctionManager::singleton->ui->removeFunctionButton->setEnabled(
				FunctionManager::singleton->ui->listWidget->count()>1);
}
void AddFunctionCommand::redo(){
	FunctionManager::singleton->ui->listWidget->addItem(func);
	FunctionManager::singleton->ui->listWidget->setCurrentItem(func);

	QObject::connect(func->start,SIGNAL(connected(Node::Socket*,Node*)),func->scene,SLOT(connectNode(Node::Socket*,Node*)));
	QObject::connect(func->start,SIGNAL(disconnected(Node::Socket*)),func->scene,SLOT(disconnectNode(Node::Socket*)));
	for(Node* n:func->iNodes){
		QObject::connect(n,SIGNAL(connected(Node::Socket*,Node*)),func->scene,SLOT(connectNode(Node::Socket*,Node*)));
		QObject::connect(n,SIGNAL(disconnected(Node::Socket*)),func->scene,SLOT(disconnectNode(Node::Socket*)));
	}
	FunctionManager::singleton->ui->removeFunctionButton->setEnabled(true);
}

RemoveFunctionCommand::RemoveFunctionCommand(QUndoCommand *parent)
	:QUndoCommand(parent){
	_rank=FunctionManager::singleton->ui->listWidget->currentRow();
}
void RemoveFunctionCommand::undo(){
	FunctionManager::singleton->ui->listWidget->insertItem(_rank,func);
	FunctionManager::singleton->ui->removeFunctionButton->setEnabled(true);
}
void RemoveFunctionCommand::redo(){
	func=(Function*)FunctionManager::singleton->ui->listWidget->takeItem(_rank);
	FunctionManager::singleton->ui->removeFunctionButton->setEnabled(
				FunctionManager::singleton->ui->listWidget->count()>1);
}

RenameFunctionCommand::RenameFunctionCommand(Function *f, const QString &to, QUndoCommand *parent)
	:QUndoCommand(parent){
	func=f;
	_from=f->text();
	_to=to;
}
void RenameFunctionCommand::undo(){
	func->setText(_from);
}
void RenameFunctionCommand::redo(){
	func->setText(_to);
}
