#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lib/RenderArea.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow){
	ui->setupUi(this);
	QWidget::setWindowTitle("PixelGates");

	ui->workspace->setRA(ui->widget);
	connect(ui->actionSQRT,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(SQRT_G);});
	connect(ui->actionADD,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(ADD_G);});
	connect(ui->actionSUB,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(SUB_G);});
	connect(ui->actionMUL,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(MUL_G);});
	connect(ui->actionDIV,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(DIV_G);});
	connect(ui->actionNEG,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(NEG_G);});
	connect(ui->actionIf,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(IF_G);});
	//connect(ui->actionAND,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(BOOL_G);});
	connect(ui->actionDouble,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(DOUBLE_G);});
	connect(ui->actionColor,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(COLOR_G);});
	connect(ui->actionPalette,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(PALETTE_G);});
	connect(ui->actionGreaterThan,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(GT_G);});
	connect(ui->actionGreaterOrEqual,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(GE_G);});
	connect(ui->actionLessThan,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(LT_G);});
	connect(ui->actionLess_Or_Equal,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(LE_G);});
	connect(ui->actionEqual,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(EQ_G);});
	connect(ui->actionNot_Equal,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(NE_G);});
	connect(ui->actionOR,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(OR_G);});
	connect(ui->actionAND,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(AND_G);});
	connect(ui->actionXOR,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(XOR_G);});
	connect(ui->actionNAND,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(NAND_G);});
	connect(ui->actionNOR,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(NOR_G);});
	connect(ui->actionXNOR,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(XNOR_G);});
	connect(ui->actionNOT,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(NOT_G);});
	connect(ui->actionX,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(X_G);});
	connect(ui->actionY,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(Y_G);});
	connect(ui->actionRender,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(RENDER_G);});
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
