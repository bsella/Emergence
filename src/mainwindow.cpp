#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "include/RenderArea.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow){
	ui->setupUi(this);
	QWidget::setWindowTitle("PixelGates");

	ui->workspace->setRA(ui->renderArea);
	connect(ui->actionSQRT,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(SQRT_G);});
	connect(ui->actionADD,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(ADD_G);});
	connect(ui->actionSUB,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(SUB_G);});
	connect(ui->actionMUL,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(MUL_G);});
	connect(ui->actionDIV,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(DIV_G);});
	connect(ui->actionNEG,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(NEG_G);});
	connect(ui->actionIf,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(IF_G);});
	//connect(ui->actionBOOL,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(BOOL_G);});
	connect(ui->actionDouble,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(DOUBLE_G);});
	connect(ui->actionColor,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(COLOR_G);});
	connect(ui->actionPalette,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(PALETTE_G);});
	connect(ui->actionGreaterThan,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(GT_G);});
	connect(ui->actionLessThan,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(LT_G);});
	connect(ui->actionEqual,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(EQ_G);});
	connect(ui->actionNot_Equal,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(NE_G);});
	connect(ui->actionOR,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(OR_G);});
	connect(ui->actionAND,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(AND_G);});
	connect(ui->actionXOR,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(XOR_G);});
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
	connect(ui->renderArea->start,SIGNAL(deleted()),this,SLOT(renderDeleted()));
	connect(ui->renderArea->xg,SIGNAL(deleted()),this,SLOT(xDeleted()));
	connect(ui->renderArea->yg,SIGNAL(deleted()),this,SLOT(yDeleted()));
	connect(ui->actionAbsolute_Value,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(ABS_G);});
	connect(ui->actionLerp,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(LERP_G);});
	connect(ui->actionClamp,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(CLAMP_G);});
	connect(ui->actionBitmap,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(BITMAP_G);});
	connect(ui->actionSin,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(SIN_G);});
	connect(ui->actionCos,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(COS_G);});
	connect(ui->actionMin,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(MIN_G);});
	connect(ui->actionMax,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(MAX_G);});

	connect(ui->actionExport,SIGNAL(triggered(bool)),this,SLOT(exportImage()));
	connect(ui->actionExit,SIGNAL(triggered(bool)), this, SLOT(close()));
	connect(ui->renderArea,&RenderArea::notValid,ui->actionExport,[this]{ui->actionExport->setEnabled(false);});
	connect(ui->renderArea,&RenderArea::valid,ui->actionExport,[this]{ui->actionExport->setEnabled(true);});
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

void MainWindow::exportImage(){
	ExportImageDialog::exportBMP(ui->renderArea);
}
