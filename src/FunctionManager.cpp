#include "headers/FunctionManager.h"
#include "ui_functionmanager.h"

FunctionManager* FunctionManager::singleton;

FunctionManager::FunctionManager(QWidget *parent):
	QDialog(parent), ui(new Ui::FunctionManager){
	ui->setupUi(this);
	addNewFunction();
	ui->workspace->setFunction((Function*)ui->listWidget->item(0));
	ui->listWidget->setItemSelected(ui->listWidget->item(0),true);
	connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(renameFunction(QListWidgetItem*)));
	connect(ui->listWidget,&QListWidget::currentItemChanged,ui->workspace,&FunctionWorkspace::_setFunction);
	singleton=this;
	connect(ui->removeFunctionButton,SIGNAL(pressed()),this,SLOT(removeCurrentFunction()));
	connect(ui->addFunctionButton,SIGNAL(pressed()),this,SLOT(addNewFunction()));
	connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
	connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
}

FunctionManager::~FunctionManager(){
	connect(ui->listWidget,&QListWidget::currentItemChanged,ui->workspace,&FunctionWorkspace::_setFunction);
	disconnect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(renameFunction(QListWidgetItem*)));
	delete ui;
}

void FunctionManager::renameFunction(QListWidgetItem *item){
	QString newname= QInputDialog::getText(this,"Change function name", "Name :");
	if(!newname.isNull())
		item->setText(newname);
}

Function* FunctionManager::getFunction(FunctionNode *node){
	if(node) singleton->ui->listWidget->setCurrentItem(node->func);
	if(singleton->exec())
		return (Function*)singleton->ui->listWidget->currentItem();
	return nullptr;
}

void FunctionManager::removeCurrentFunction()const{
	delete ui->listWidget->takeItem(ui->listWidget->currentRow());
	if(ui->listWidget->count()<=1)
		ui->removeFunctionButton->setEnabled(false);
}
void FunctionManager::addNewFunction()const{
	Function* func= new Function;
	ui->listWidget->addItem(func);
	ui->listWidget->setCurrentItem(func);
	connect(func->start,SIGNAL(connected(Node::Socket*,Node*)),ui->workspace,SLOT(connectNode(Node::Socket*,Node*)));
	connect(func->start,SIGNAL(disconnected(Node::Socket*)),ui->workspace,SLOT(disconnectNode(Node::Socket*)));
	for(Node* n:func->iNodes){
		connect(n,SIGNAL(connected(Node::Socket*,Node*)),ui->workspace,SLOT(connectNode(Node::Socket*,Node*)));
		connect(n,SIGNAL(disconnected(Node::Socket*)),ui->workspace,SLOT(disconnectNode(Node::Socket*)));
	}
	ui->removeFunctionButton->setEnabled(true);
}

void FunctionManager::on_spinBox_valueChanged(int arg1){
	ui->workspace->func->changeNbArgs(arg1);
	ui->workspace->updateFunctionNodes();
}
