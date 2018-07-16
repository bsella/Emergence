#include "headers/FunctionManager.h"
#include "ui_functionmanager.h"

FunctionManager::FunctionManager(QWidget *parent):
	QDialog(parent), ui(new Ui::FunctionManager){
	ui->setupUi(this);
	addFunction("new Function",2);
	connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(renameFunction(QListWidgetItem*)));
}

void FunctionManager::addFunction(const QString& name, uint nbArgs){
	Function *func= new Function(name, nbArgs);
	ui->listWidget->addItem(func);
	connect(func->start,SIGNAL(connected(Node::Socket*,Node*)),ui->workspace,SLOT(connectNode(Node::Socket*,Node*)));
	connect(func->start,SIGNAL(disconnected(Node::Socket*)),ui->workspace,SLOT(disconnectNode(Node::Socket*)));
	for(Node* n:func->iNodes){
		connect(n,SIGNAL(connected(Node::Socket*,Node*)),ui->workspace,SLOT(connectNode(Node::Socket*,Node*)));
		connect(n,SIGNAL(disconnected(Node::Socket*)),ui->workspace,SLOT(disconnectNode(Node::Socket*)));
	}
	ui->workspace->setFunction(func);
}

FunctionManager::~FunctionManager(){
	disconnect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(renameFunction(QListWidgetItem*)));
	delete ui;
}

void FunctionManager::renameFunction(QListWidgetItem *item){
	QString newname= QInputDialog::getText(this,"Change function name", "Name :");
	if(!newname.isNull())
		item->setText(newname);
}
