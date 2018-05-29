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
	connect(ui->actionComplex,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(CPLX_G);});
	connect(ui->actionSQRT,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(SQRT_G);});
	connect(ui->actionADD,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(ADD_G);});
	connect(ui->actionSUB,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(SUB_G);});
	connect(ui->actionMUL,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(MUL_G);});
	connect(ui->actionDIV,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(DIV_G);});
	connect(ui->actionNEG,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(NEG_G);});
	connect(ui->actionIf,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(IF_G);});
	connect(ui->actionDouble,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(DOUBLE_G);});
	connect(ui->actionColor,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(COLOR_G);});
	connect(ui->actionLUT,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(PALETTE_G);});
	connect(ui->actionGreaterThan,	&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(GT_G);});
	connect(ui->actionLessThan,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(LT_G);});
	connect(ui->actionEqual,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(EQ_G);});
	connect(ui->actionNot_Equal,	&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(NE_G);});
	connect(ui->actionOR,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(OR_G);});
	connect(ui->actionAND,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(AND_G);});
	connect(ui->actionXOR,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(XOR_G);});
	connect(ui->actionNOT,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(NOT_G);});
	connect(ui->actionABS,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(ABS_G);});
	connect(ui->actionLerp,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(LERP_G);});
	connect(ui->actionClamp,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(CLAMP_G);});
	connect(ui->actionBitmap,		&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(BITMAP_G);});
	connect(ui->actionSin,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(SIN_G);});
	connect(ui->actionCos,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(COS_G);});
	connect(ui->actionMin,			&QAction::triggered,ui->workspace,[this]{ui->workspace->addNode(MIN_G);});
	connect(ui->actionMax,			&QAction::triggered,ui->workspace,[&]{ui->workspace->addNode(MAX_G);});
	connect(ui->actionX,			&QAction::triggered,ui->workspace,[this]{
		ui->workspace->addNode(X_G);
		ui->actionX->setEnabled(false);
		ui->toolBox->x->setEnabled(false);
	});
	connect(ui->actionY,			&QAction::triggered,ui->workspace,[this]{
		ui->workspace->addNode(Y_G);
		ui->actionY->setEnabled(false);
		ui->toolBox->y->setEnabled(false);
	});
	connect(ui->actionRatio,			&QAction::triggered,ui->workspace,[this]{
		ui->workspace->addNode(RATIO_G);
		ui->actionRatio->setEnabled(false);
		ui->toolBox->ratio->setEnabled(false);
	});
	connect(ui->actionRender,		&QAction::triggered,ui->workspace,[this]{
		ui->workspace->addNode(RENDER_G);
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

	copy=new QShortcut(QKeySequence("Ctrl+C"),this);
	connect(copy,SIGNAL(activated()),ui->workspace,SLOT(copy()));
	paste=new QShortcut(QKeySequence("Ctrl+V"),this);
	connect(paste,SIGNAL(activated()),ui->workspace,SLOT(paste()));
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

