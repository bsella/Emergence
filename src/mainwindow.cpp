#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/RenderArea.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow){
	ui->setupUi(this);
	QWidget::setWindowTitle("PixelGates");
	QWidget::setWindowIcon(QIcon(":/icons/PG.ico"));

	ui->workspace->setRA(ui->renderArea);
	connect(ui->actionSQRT,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(SQRT_G,false);});
	connect(ui->actionADD,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(ADD_G,false);});
	connect(ui->actionSUB,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(SUB_G,false);});
	connect(ui->actionMUL,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(MUL_G,false);});
	connect(ui->actionDIV,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(DIV_G,false);});
	connect(ui->actionNEG,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(NEG_G,false);});
	connect(ui->actionIf,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(IF_G,false);});
	//connect(ui->actionBOOL,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(BOOL_G,false);});
	connect(ui->actionDouble,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(DOUBLE_G,false);});
	connect(ui->actionColor,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(COLOR_G,false);});
	connect(ui->actionLUT,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(PALETTE_G,false);});
	connect(ui->actionGreaterThan,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(GT_G,false);});
	connect(ui->actionLessThan,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(LT_G,false);});
	connect(ui->actionEqual,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(EQ_G,false);});
	connect(ui->actionNot_Equal,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(NE_G,false);});
	connect(ui->actionOR,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(OR_G,false);});
	connect(ui->actionAND,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(AND_G,false);});
	connect(ui->actionXOR,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(XOR_G,false);});
	connect(ui->actionNOT,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(NOT_G,false);});
	connect(ui->actionX,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(X_G,false);});
	connect(ui->actionY,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(Y_G,false);});
	connect(ui->actionRender,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(RENDER_G,false);});
	connect(ui->actionAbsolute_Value,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(ABS_G,false);});
	connect(ui->actionLerp,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(LERP_G,false);});
	connect(ui->actionClamp,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(CLAMP_G,false);});
	connect(ui->actionBitmap,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(BITMAP_G,false);});
	connect(ui->actionSin,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(SIN_G,false);});
	connect(ui->actionCos,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(COS_G,false);});
	connect(ui->actionMin,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(MIN_G,false);});
	connect(ui->actionMax,&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncGate(MAX_G,false);});
	connect(ui->actionRender,SIGNAL(triggered(bool)),ui->actionRender,SLOT(setEnabled(bool)));
	connect(ui->actionX,SIGNAL(triggered(bool)),ui->actionX,SLOT(setEnabled(bool)));
	connect(ui->actionY,SIGNAL(triggered(bool)),ui->actionY,SLOT(setEnabled(bool)));
	ui->actionRender->setEnabled(false);
	ui->actionX->setEnabled(false);
	ui->actionY->setEnabled(false);
	connect(ui->renderArea->start,SIGNAL(deleted()),this,SLOT(renderDeleted()));
	connect(ui->renderArea->xg,SIGNAL(deleted()),this,SLOT(xDeleted()));
	connect(ui->renderArea->yg,SIGNAL(deleted()),this,SLOT(yDeleted()));

	connect(ui->actionExport,SIGNAL(triggered(bool)),this,SLOT(exportImage()));
	connect(ui->actionExit,SIGNAL(triggered(bool)), this, SLOT(close()));
	connect(ui->renderArea,&RenderArea::notValid,ui->actionExport,[this]{ui->actionExport->setEnabled(false);});
	connect(ui->renderArea,&RenderArea::valid,ui->actionExport,[this]{ui->actionExport->setEnabled(true);});
	///TODO
	ui->actionBool->setEnabled(false);
	connect(ui->actionSave_as,SIGNAL(triggered(bool)),ui->workspace,SLOT(createFile()));
	connect(ui->actionOpen,SIGNAL(triggered(bool)),ui->workspace,SLOT(loadGatesFromFile()));

	connect(ui->sqrtButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(SQRT_G,false);});
	connect(ui->addButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(ADD_G,false);});
	connect(ui->subButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(SUB_G,false);});
	connect(ui->mulButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(MUL_G,false);});
	connect(ui->divButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(DIV_G,false);});
	connect(ui->negButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(NEG_G,false);});
//	connect(ui->actionIf,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(IF_G,false);});
	//connect(ui->actionBOOL,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(BOOL_G,false);});
//	connect(ui->actionDouble,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(DOUBLE_G,false);});
//	connect(ui->actionColor,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(COLOR_G,false);});
//	connect(ui->actionLUT,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(PALETTE_G,false);});
	connect(ui->gtButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(GT_G,false);});
	connect(ui->ltButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(LT_G,false);});
	connect(ui->eqButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(EQ_G,false);});
	connect(ui->neButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(NE_G,false);});
	connect(ui->orButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(OR_G,false);});
	connect(ui->andButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(AND_G,false);});
	connect(ui->xorButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(XOR_G,false);});
	connect(ui->notButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(NOT_G,false);});
//	connect(ui->actionX,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(X_G,false);});
//	connect(ui->actionY,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(Y_G,false);});
//	connect(ui->actionRender,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(RENDER_G,false);});
	connect(ui->absButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(ABS_G,false);});
	connect(ui->lerpButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(LERP_G,false);});
	connect(ui->clampButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(CLAMP_G,false);});
//	connect(ui->actionBitmap,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(BITMAP_G,false);});
	connect(ui->sinButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(SIN_G,false);});
	connect(ui->cosButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(COS_G,false);});
	connect(ui->minButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(MIN_G,false);});
	connect(ui->maxButton,&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncGate(MAX_G,false);});
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
