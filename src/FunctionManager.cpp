#include "headers/FunctionManager.h"
#include "ui_functionmanager.h"

FunctionManager::FunctionManager(QWidget *parent):
	QDialog(parent), ui(new Ui::FunctionManager){
	ui->setupUi(this);
	connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(renameFunction(QListWidgetItem*)));
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
