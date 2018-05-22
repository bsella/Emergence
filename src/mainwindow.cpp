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
	connect(ui->actionComplex,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(CPLX_G);});
	connect(ui->actionSQRT,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(SQRT_G);});
	connect(ui->actionADD,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(ADD_G);});
	connect(ui->actionSUB,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(SUB_G);});
	connect(ui->actionMUL,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(MUL_G);});
	connect(ui->actionDIV,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(DIV_G);});
	connect(ui->actionNEG,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(NEG_G);});
	connect(ui->actionIf,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(IF_G);});
	connect(ui->actionDouble,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(DOUBLE_G);});
	connect(ui->actionColor,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(COLOR_G);});
	connect(ui->actionLUT,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(PALETTE_G);});
	connect(ui->actionGreaterThan,	&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(GT_G);});
	connect(ui->actionLessThan,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(LT_G);});
	connect(ui->actionEqual,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(EQ_G);});
	connect(ui->actionNot_Equal,	&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(NE_G);});
	connect(ui->actionOR,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(OR_G);});
	connect(ui->actionAND,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(AND_G);});
	connect(ui->actionXOR,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(XOR_G);});
	connect(ui->actionNOT,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(NOT_G);});
	connect(ui->actionABS,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(ABS_G);});
	connect(ui->actionLerp,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(LERP_G);});
	connect(ui->actionClamp,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(CLAMP_G);});
	connect(ui->actionBitmap,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(BITMAP_G);});
	connect(ui->actionSin,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(SIN_G);});
	connect(ui->actionCos,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(COS_G);});
	connect(ui->actionMin,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addFuncNode(MIN_G);});
	connect(ui->actionMax,			&QAction::triggered,ui->workspace,[&]{ui->workspace->addFuncNode(MAX_G);});
	connect(ui->actionX,			&QAction::triggered,ui->workspace,[this]{
		ui->workspace->addFuncNode(X_G);
		ui->actionX->setEnabled(false);
		ui->toolBox->x->setEnabled(false);
	});
	connect(ui->actionY,			&QAction::triggered,ui->workspace,[this]{
		ui->workspace->addFuncNode(Y_G);
		ui->actionY->setEnabled(false);
		ui->toolBox->y->setEnabled(false);
	});
	connect(ui->actionRatio,			&QAction::triggered,ui->workspace,[this]{
		ui->workspace->addFuncNode(RATIO_G);
		ui->actionRatio->setEnabled(false);
		ui->toolBox->ratio->setEnabled(false);
	});
	connect(ui->actionRender,		&QAction::triggered,ui->workspace,[this]{
		ui->workspace->addFuncNode(RENDER_G);
		ui->actionRender->setEnabled(false);
		ui->toolBox->output->setEnabled(false);
	});

	connect(ui->renderArea,		SIGNAL(valid(bool)),ui->actionExport,SLOT(setEnabled(bool)));

	connect(ui->renderArea->xg,	&PixelXNode::deleted,ui->actionX,[&]{
		ui->actionX->setEnabled(true);
		ui->toolBox->x->setEnabled(true);
	});
	connect(ui->renderArea->yg,	&PixelXNode::deleted,ui->actionY,[&]{
		ui->actionY->setEnabled(true);
		ui->toolBox->y->setEnabled(true);
	});
	connect(ui->renderArea->ratio,	&PixelXNode::deleted,ui->actionRatio,[&]{
		ui->actionRatio->setEnabled(true);
		ui->toolBox->ratio->setEnabled(true);
	});
	connect(ui->renderArea->start,&PixelXNode::deleted,ui->actionRender,[&]{
		ui->actionRender->setEnabled(true);
		ui->toolBox->output->setEnabled(true);
	});

	ui->actionRender->setEnabled(false);
	ui->actionX->setEnabled(false);
	ui->actionY->setEnabled(false);
	ui->toolBox->x->setEnabled(false);
	ui->toolBox->y->setEnabled(false);
	ui->toolBox->output->setEnabled(false);
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

