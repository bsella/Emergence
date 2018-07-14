#include "headers/FunctionManager.h"
#include "ui_functionmanager.h"

FunctionManager::FunctionManager(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::FunctionManager)
{
	ui->setupUi(this);
}

FunctionManager::~FunctionManager()
{
	delete ui;
}
