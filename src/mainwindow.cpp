#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lib/RenderArea.h"
#include "lib/CompGate.h"
#include "lib/PaletteGate.h"
#include "lib/IfGate.h"
#include "lib/ConstGate.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow){
	ui->setupUi(this);
	QWidget::setWindowTitle("PixelGates");

	ui->workspace->setRA(ui->widget);
	connect(ui->actionIf,SIGNAL(triggered(bool)),ui->workspace,SLOT(addIFGate()));
	connect(ui->actionGreaterThan,SIGNAL(triggered(bool)),ui->workspace,SLOT(addGTGate()));
	connect(ui->actionGreaterOrEqual,SIGNAL(triggered(bool)),ui->workspace,SLOT(addGEGate()));
	connect(ui->actionLessThan,SIGNAL(triggered(bool)),ui->workspace,SLOT(addLTGate()));
	connect(ui->actionLess_Or_Equal,SIGNAL(triggered(bool)),ui->workspace,SLOT(addLEGate()));
	connect(ui->actionEqual,SIGNAL(triggered(bool)),ui->workspace,SLOT(addEQGate()));
	connect(ui->actionNot_Equal,SIGNAL(triggered(bool)),ui->workspace,SLOT(addNEGate()));
	connect(ui->actionAND,SIGNAL(triggered(bool)),ui->workspace,SLOT(addANDGate()));
	connect(ui->actionOR,SIGNAL(triggered(bool)),ui->workspace,SLOT(addORGate()));
	connect(ui->actionXOR,SIGNAL(triggered(bool)),ui->workspace,SLOT(addXORGate()));
	connect(ui->actionNAND,SIGNAL(triggered(bool)),ui->workspace,SLOT(addNANDGate()));
	connect(ui->actionNOR,SIGNAL(triggered(bool)),ui->workspace,SLOT(addNORGate()));
	connect(ui->actionXNOR,SIGNAL(triggered(bool)),ui->workspace,SLOT(addXNORGate()));
	connect(ui->actionNOT,SIGNAL(triggered(bool)),ui->workspace,SLOT(addNOTGate()));
	connect(ui->actionColor,SIGNAL(triggered(bool)),ui->workspace,SLOT(addCColorGate()));
	connect(ui->actionDouble,SIGNAL(triggered(bool)),ui->workspace,SLOT(addCNumberGate()));
	connect(ui->actionRender,SIGNAL(triggered(bool)),ui->workspace,SLOT(addRenderGate()));
	connect(ui->actionX,SIGNAL(triggered(bool)),ui->workspace,SLOT(addXGate()));
	connect(ui->actionY,SIGNAL(triggered(bool)),ui->workspace,SLOT(addYGate()));
	connect(ui->actionRender,SIGNAL(triggered(bool)),ui->actionRender,SLOT(setEnabled(bool)));
	connect(ui->actionX,SIGNAL(triggered(bool)),ui->actionX,SLOT(setEnabled(bool)));
	connect(ui->actionY,SIGNAL(triggered(bool)),ui->actionY,SLOT(setEnabled(bool)));
	ui->actionRender->setEnabled(false);
	ui->actionX->setEnabled(false);
	ui->actionY->setEnabled(false);
	connect(ui->widget->start,SIGNAL(deleted()),this,SLOT(renderDeleted()));
	connect(ui->widget->xg,SIGNAL(deleted()),this,SLOT(xDeleted()));
	connect(ui->widget->yg,SIGNAL(deleted()),this,SLOT(yDeleted()));

	///TODO
	ui->actionPalette->setEnabled(false);
	ui->actionBool->setEnabled(false);
}

MainWindow::~MainWindow(){
	delete ui;
}

void MainWindow::renderDeleted(){
	ui->actionRender->setEnabled(true);
}
void MainWindow::xDeleted(){
	ui->actionX->setEnabled(true);
}
void MainWindow::yDeleted(){
	ui->actionY->setEnabled(true);
}
