#include "FunctionManager.h"
#include "ui_functionmanager.h"

FunctionManager* FunctionManager::singleton=0;
FunctionManager* FunctionManager::instance(){
	if(singleton==0)
		singleton= new FunctionManager;
	return singleton;
}
FunctionManager::FunctionManager(QWidget *parent):
	QDialog(parent), ui(new Ui::FunctionManager){
	ui->setupUi(this);
	ui->workspace->setAcceptDrops(true);
	ui->workspace->setDragMode(QGraphicsView::DragMode::RubberBandDrag);
	ui->removeFunctionButton->setEnabled(false);
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

Function* FunctionManager::functionAt(int i){
	return (Function*)instance()->ui->listWidget->item(i);
}
int FunctionManager::indexOf(Function *f){
	return instance()->ui->listWidget->row(f);
}
int FunctionManager::count(){
	return instance()->ui->listWidget->count();
}

void FunctionManager::on_addFunctionButton_clicked(){
	undoStack.push(new AddFunctionCommand);
}
void FunctionManager::on_removeFunctionButton_clicked(){
	undoStack.push(new RemoveFunctionCommand);
}
void FunctionManager::renameFunction(QListWidgetItem *item){
	QString newname= QInputDialog::getText(this,"Change function name", "Name :");
	if(!newname.isNull()){
		newname.replace(' ','_');
		undoStack.push(new RenameFunctionCommand((Function*)item,newname));
	}
}

Function* FunctionManager::getFunction(FunctionNode *node){
	if(node) instance()->ui->listWidget->setCurrentItem(node->func);
	if(instance()->exec())
		return (Function*)instance()->ui->listWidget->currentItem();
	return nullptr;
}

bool FunctionManager::userIntented=true;

void FunctionManager::on_spinBox_valueChanged(int arg1){
	if(userIntented){
		Function* func=(Function*)ui->listWidget->currentItem();
		func->scene->undoStack.push(new ChangeNbArgsCommand(func,func->nbArgs,arg1));
	}
}

void FunctionManager::setFunction(QListWidgetItem* curr, QListWidgetItem* prev){
	if(!curr){
		ui->workspace->setScene(0);
		ui->spinBox->setEnabled(false);
		ui->removeFunctionButton->setEnabled(false);
		return;
	}
	ui->spinBox->setEnabled(true);
	ui->removeFunctionButton->setEnabled(true);
	if(Function* fPrev=(Function*)prev){
		disconnect(&redo,SIGNAL(triggered(bool)),&fPrev->scene->undoStack,SLOT(redo()));
		disconnect(&undo,SIGNAL(triggered(bool)),&fPrev->scene->undoStack,SLOT(undo()));
		disconnect(&select_all,SIGNAL(triggered(bool)),fPrev->scene,SLOT(select_all()));
		disconnect(&paste,SIGNAL(triggered(bool)),fPrev->scene,SLOT(paste()));
		disconnect(&cut,SIGNAL(triggered(bool)),fPrev->scene,SLOT(cut()));
		disconnect(&copy,SIGNAL(triggered(bool)),fPrev->scene,SLOT(copy()));
		disconnect(&del,SIGNAL(triggered(bool)),fPrev->scene,SLOT(delete_selected()));
	}
	if(Function* fCurr=(Function*)curr){
		ui->workspace->setScene(fCurr->scene);
		userIntented=false;
		ui->spinBox->setValue(fCurr->nbArgs);
		userIntented=true;
		connect(&del,SIGNAL(triggered(bool)),fCurr->scene,SLOT(delete_selected()));
		connect(&copy,SIGNAL(triggered(bool)),fCurr->scene,SLOT(copy()));
		connect(&cut,SIGNAL(triggered(bool)),fCurr->scene,SLOT(cut()));
		connect(&paste,SIGNAL(triggered(bool)),fCurr->scene,SLOT(paste()));
		connect(&select_all,SIGNAL(triggered(bool)),fCurr->scene,SLOT(select_all()));
		connect(&undo,SIGNAL(triggered(bool)),&fCurr->scene->undoStack,SLOT(undo()));
		connect(&redo,SIGNAL(triggered(bool)),&fCurr->scene->undoStack,SLOT(redo()));
	}
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
			func->iNodes.push_back(new Function::FunctionInputNode(i));
			func->scene->addItem(func->iNodes[i]);
		}
	func->nbArgs=_from;
	FunctionManager::userIntented=false;
	FunctionManager::instance()->ui->spinBox->setValue(_from);
	FunctionManager::userIntented=true;
	func->scene->update();
}
void ChangeNbArgsCommand::redo(){
	if(_to>_from)
		for(int i=_from; i<_to; i++){
			func->iNodes.push_back(new Function::FunctionInputNode(i));
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
	FunctionManager::instance()->ui->spinBox->setValue(_to);
	FunctionManager::userIntented=true;
	func->scene->update();
}

AddFunctionCommand::AddFunctionCommand(QUndoCommand*parent)
	:QUndoCommand(parent){
	func= new Function(0,"New_Function");
}
void AddFunctionCommand::undo(){
	QObject::disconnect(func->start,SIGNAL(disconnected(Node::Socket*)),func->scene,SLOT(disconnectNode(Node::Socket*)));
	QObject::disconnect(func->start,SIGNAL(connected(Node::Socket*,Node*)),func->scene,SLOT(connectNode(Node::Socket*,Node*)));
	for(Node* n:func->iNodes){
		QObject::disconnect(n,SIGNAL(connected(Node::Socket*,Node*)),func->scene,SLOT(connectNode(Node::Socket*,Node*)));
		QObject::disconnect(n,SIGNAL(disconnected(Node::Socket*)),func->scene,SLOT(disconnectNode(Node::Socket*)));
	}
	delete func;
	FunctionManager::instance()->ui->removeFunctionButton->setEnabled(
				FunctionManager::instance()->ui->listWidget->count()>1);
}
void AddFunctionCommand::redo(){
	FunctionManager::instance()->ui->listWidget->addItem(func);

	QObject::connect(func->start,SIGNAL(connected(Node::Socket*,Node*)),func->scene,SLOT(connectNode(Node::Socket*,Node*)));
	QObject::connect(func->start,SIGNAL(disconnected(Node::Socket*)),func->scene,SLOT(disconnectNode(Node::Socket*)));
	for(Node* n:func->iNodes){
		QObject::connect(n,SIGNAL(connected(Node::Socket*,Node*)),func->scene,SLOT(connectNode(Node::Socket*,Node*)));
		QObject::connect(n,SIGNAL(disconnected(Node::Socket*)),func->scene,SLOT(disconnectNode(Node::Socket*)));
	}
	FunctionManager::instance()->ui->removeFunctionButton->setEnabled(true);
}

RemoveFunctionCommand::RemoveFunctionCommand(QUndoCommand *parent)
	:QUndoCommand(parent){
	_rank=FunctionManager::instance()->ui->listWidget->currentRow();
}
void RemoveFunctionCommand::undo(){
	FunctionManager::instance()->ui->listWidget->insertItem(_rank,func);
	FunctionManager::instance()->ui->removeFunctionButton->setEnabled(true);
}
void RemoveFunctionCommand::redo(){
	func=(Function*)FunctionManager::instance()->ui->listWidget->takeItem(_rank);
	FunctionManager::instance()->ui->removeFunctionButton->setEnabled(
				FunctionManager::instance()->ui->listWidget->count());
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

void FunctionManager::clear(){
	instance()->ui->workspace->setScene(0);
	while(instance()->ui->listWidget->count())
		delete instance()->ui->listWidget->takeItem(0);
	instance()->ui->removeFunctionButton->setEnabled(false);
	instance()->ui->spinBox->setEnabled(false);
}
void FunctionManager::fromBin(std::istream& in)const{
	Function *f= new Function;
	std::string str;
	in >> str;
	in.ignore(1);
	f->setText(QString::fromStdString(str));
	f->scene->fromBin(in);

	f->start= f->getOutputFromScene();
	in.read(reinterpret_cast<char*>(&f->nbArgs),sizeof(int));
	for(int i=0; i<f->nbArgs;i++)
		f->iNodes.push_back(f->getNthInputFromScene(i));
	ui->listWidget->addItem(f);
}
void FunctionManager::fromText(std::istream& in)const{
	Function *f= new Function;
	std::string str;
	in >> str;
	f->setText(QString::fromStdString(str));
	f->scene->fromText(in);

	f->start= f->getOutputFromScene();
	in >> f->nbArgs;
	for(int i=0; i<f->nbArgs;i++)
		f->iNodes.push_back(f->getNthInputFromScene(i));
	ui->listWidget->addItem(f);
}
