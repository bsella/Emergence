#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/RenderArea.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow){
	ui->setupUi(this);
	QWidget::setWindowTitle("Emergence");
	QWidget::setWindowIcon(QIcon(":/icons/emgc.ico"));

	ui->workspace->setRA(ui->renderArea);
	connect(ui->actionSQRT,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(SQRT_G,false);});
	connect(ui->actionADD,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(ADD_G,false);});
	connect(ui->actionSUB,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(SUB_G,false);});
	connect(ui->actionMUL,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(MUL_G,false);});
	connect(ui->actionDIV,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(DIV_G,false);});
	connect(ui->actionNEG,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(NEG_G,false);});
	connect(ui->actionIf,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(IF_G,false);});
	connect(ui->actionDouble,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(DOUBLE_G,false);});
	connect(ui->actionColor,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(COLOR_G,false);});
	connect(ui->actionLUT,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(PALETTE_G,false);});
	connect(ui->actionGreaterThan,	&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(GT_G,false);});
	connect(ui->actionLessThan,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(LT_G,false);});
	connect(ui->actionEqual,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(EQ_G,false);});
	connect(ui->actionNot_Equal,	&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(NE_G,false);});
	connect(ui->actionOR,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(OR_G,false);});
	connect(ui->actionAND,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(AND_G,false);});
	connect(ui->actionXOR,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(XOR_G,false);});
	connect(ui->actionNOT,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(NOT_G,false);});
	connect(ui->actionABS,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(ABS_G,false);});
	connect(ui->actionLerp,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(LERP_G,false);});
	connect(ui->actionClamp,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(CLAMP_G,false);});
	connect(ui->actionBitmap,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(BITMAP_G,false);});
	connect(ui->actionSin,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(SIN_G,false);});
	connect(ui->actionCos,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(COS_G,false);});
	connect(ui->actionMin,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(MIN_G,false);});
	connect(ui->actionMax,			&QAction::triggered,ui->workspace,[&]{ui->workspace->addFuncNode(MAX_G,false);});
	connect(ui->actionX,			&QAction::triggered,ui->workspace,[this]{
		ui->workspace->addFuncNode(X_G,false);
		ui->actionX->setEnabled(false);
		ui->xButton->setEnabled(false);
	});
	connect(ui->actionY,			&QAction::triggered,ui->workspace,[this]{
		ui->workspace->addFuncNode(Y_G,false);
		ui->actionY->setEnabled(false);
		ui->yButton->setEnabled(false);
	});
	connect(ui->actionRatio,			&QAction::triggered,ui->workspace,[this]{
		ui->workspace->addFuncNode(RATIO_G,false);
		ui->actionRatio->setEnabled(false);
		ui->ratioButton->setEnabled(false);
	});
	connect(ui->actionRender,		&QAction::triggered,ui->workspace,[this]{
		ui->workspace->addFuncNode(RENDER_G,false);
		ui->actionRender->setEnabled(false);
		ui->renderButton->setEnabled(false);
	});

	connect(ui->renderArea,		SIGNAL(valid(bool)),ui->actionExport,SLOT(setEnabled(bool)));

	connect(ui->sqrtButton,		&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncNode(SQRT_G,false);});
	connect(ui->addButton,		&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncNode(ADD_G,false);});
	connect(ui->subButton,		&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncNode(SUB_G,false);});
	connect(ui->mulButton,		&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncNode(MUL_G,false);});
	connect(ui->divButton,		&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncNode(DIV_G,false);});
	connect(ui->negButton,		&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncNode(NEG_G,false);});
	connect(ui->ifButton,		&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncNode(IF_G,false);});
	connect(ui->numButton,		&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncNode(DOUBLE_G,false);});
	connect(ui->colorButton,	&QToolButton::clicked,ui->workspace,[this]{ui->workspace->addFuncNode(COLOR_G,false);});
	connect(ui->lutButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(PALETTE_G,false);});
	connect(ui->gtButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(GT_G,false);});
	connect(ui->ltButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(LT_G,false);});
	connect(ui->eqButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(EQ_G,false);});
	connect(ui->neButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(NE_G,false);});
	connect(ui->orButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(OR_G,false);});
	connect(ui->andButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(AND_G,false);});
	connect(ui->xorButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(XOR_G,false);});
	connect(ui->notButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(NOT_G,false);});
	connect(ui->absButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(ABS_G,false);});
	connect(ui->lerpButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(LERP_G,false);});
	connect(ui->clampButton,	&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(CLAMP_G,false);});
	connect(ui->imgButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(BITMAP_G,false);});
	connect(ui->sinButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(SIN_G,false);});
	connect(ui->cosButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(COS_G,false);});
	connect(ui->minButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(MIN_G,false);});
	connect(ui->maxButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(MAX_G,false);});
	connect(ui->rgbButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(RGB_G,false);});
	connect(ui->hsvButton,		&QToolButton::clicked,ui->workspace,[&]{ui->workspace->addFuncNode(HSV_G,false);});
	connect(ui->xButton,		SIGNAL(clicked()),ui->actionX,SLOT(trigger()));
	connect(ui->yButton,		SIGNAL(clicked()),ui->actionY,SLOT(trigger()));
	connect(ui->ratioButton,	SIGNAL(clicked()),ui->actionRatio,SLOT(trigger()));
	connect(ui->renderButton,	SIGNAL(clicked()),ui->actionRender,SLOT(trigger()));

	connect(ui->renderArea->xg,	&PixelXNode::deleted,ui->actionX,[&]{
		ui->actionX->setEnabled(true);
		ui->xButton->setEnabled(true);
	});
	connect(ui->renderArea->yg,	&PixelXNode::deleted,ui->actionY,[&]{
		ui->actionY->setEnabled(true);
		ui->yButton->setEnabled(true);
	});
	connect(ui->renderArea->ratio,	&PixelXNode::deleted,ui->actionRatio,[&]{
		ui->actionRatio->setEnabled(true);
		ui->ratioButton->setEnabled(true);
	});
	connect(ui->renderArea->start,&PixelXNode::deleted,ui->actionRender,[&]{
		ui->actionRender->setEnabled(true);
		ui->renderButton->setEnabled(true);
	});
	ui->actionRender->setEnabled(false);
	ui->actionX->setEnabled(false);
	ui->actionY->setEnabled(false);
	ui->renderButton->setEnabled(false);
	ui->xButton->setEnabled(false);
	ui->yButton->setEnabled(false);
}

MainWindow::~MainWindow(){
	delete ui;
}

void MainWindow::on_actionExit_triggered(){
	close();
}

void MainWindow::on_actionExport_triggered(){
	ExportImageDialog::exportBMP(ui->renderArea);
}

void MainWindow::on_actionSave_as_triggered(){
	ui->workspace->createFile();
}

void MainWindow::on_actionOpen_triggered(){
	ui->workspace->loadNodesFromFile();
}

