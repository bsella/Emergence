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

	ui->actionUndo->setEnabled(false);
	ui->actionRedo->setEnabled(false);

	copy=new QShortcut(QKeySequence("Ctrl+C"),this);
	connect(copy,SIGNAL(activated()),ui->workspace,SLOT(copy()));
	cut=new QShortcut(QKeySequence("Ctrl+X"),this);
	connect(cut,SIGNAL(activated()),ui->workspace,SLOT(cut()));
	paste=new QShortcut(QKeySequence("Ctrl+V"),this);
	connect(paste,SIGNAL(activated()),ui->workspace,SLOT(paste()));
	open=new QShortcut(QKeySequence("Ctrl+O"),this);
	connect(open,SIGNAL(activated()),ui->workspace,SLOT(load()));
	save=new QShortcut(QKeySequence("Ctrl+S"),this);
	connect(save,SIGNAL(activated()),ui->workspace,SLOT(save()));
	remove=new QShortcut(QKeySequence("Delete"),this);
	connect(remove,SIGNAL(activated()),ui->workspace,SLOT(delete_selected()));
	select_all=new QShortcut(QKeySequence("Ctrl+A"),this);
	connect(select_all,SIGNAL(activated()),ui->workspace,SLOT(select_all()));


	connect(ui->actionCopy,&QAction::triggered,ui->workspace,&Workspace::copy);
	connect(ui->actionPaste,&QAction::triggered,ui->workspace,&Workspace::paste);
	connect(ui->actionCut,&QAction::triggered,ui->workspace,&Workspace::cut);
	connect(ui->actionDelete,&QAction::triggered,ui->workspace,&Workspace::delete_selected);
	connect(ui->actionSelect_all,&QAction::triggered,ui->workspace,&Workspace::select_all);
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
	ui->workspace->save();
}
void MainWindow::on_actionOpen_triggered(){
	ui->workspace->load();
}
void MainWindow::on_actionIf_triggered(){
	ui->workspace->addNode(IF_G);
}
void MainWindow::on_actionGreaterThan_triggered(){
	ui->workspace->addNode(GT_G);
}
void MainWindow::on_actionLessThan_triggered(){
	ui->workspace->addNode(LT_G);
}
void MainWindow::on_actionEqual_triggered(){
	ui->workspace->addNode(EQ_G);
}
void MainWindow::on_actionNot_Equal_triggered(){
	ui->workspace->addNode(NE_G);
}
void MainWindow::on_actionAND_triggered(){
	ui->workspace->addNode(AND_G);
}
void MainWindow::on_actionOR_triggered(){
	ui->workspace->addNode(OR_G);
}
void MainWindow::on_actionXOR_triggered(){
	ui->workspace->addNode(XOR_G);
}
void MainWindow::on_actionNOT_triggered(){
	ui->workspace->addNode(NOT_G);
}
void MainWindow::on_actionDouble_triggered(){
	ui->workspace->addNode(DOUBLE_G);
}
void MainWindow::on_actionColor_triggered(){
	ui->workspace->addNode(COLOR_G);
}
void MainWindow::on_actionLUT_triggered(){
	ui->workspace->addNode(PALETTE_G);
}
void MainWindow::on_actionX_triggered(){
	ui->workspace->addNode(X_G);
	ui->actionX->setEnabled(false);
	ui->toolBox->x->setEnabled(false);
}
void MainWindow::on_actionY_triggered(){
	ui->workspace->addNode(Y_G);
	ui->actionY->setEnabled(false);
	ui->toolBox->y->setEnabled(false);
}
void MainWindow::on_actionRender_triggered(){
	ui->workspace->addNode(RENDER_G);
	ui->actionRender->setEnabled(false);
	ui->toolBox->output->setEnabled(false);
}
void MainWindow::on_actionADD_triggered(){
	ui->workspace->addNode(ADD_G);
}
void MainWindow::on_actionSUB_triggered(){
	ui->workspace->addNode(SUB_G);
}
void MainWindow::on_actionMUL_triggered(){
	ui->workspace->addNode(MUL_G);
}
void MainWindow::on_actionDIV_triggered(){
	ui->workspace->addNode(DIV_G);
}
void MainWindow::on_actionNEG_triggered(){
	ui->workspace->addNode(NEG_G);
}
void MainWindow::on_actionSQRT_triggered(){
	ui->workspace->addNode(SQRT_G);
}
void MainWindow::on_actionABS_triggered(){
	ui->workspace->addNode(ABS_G);
}
void MainWindow::on_actionLerp_triggered(){
	ui->workspace->addNode(LERP_G);
}
void MainWindow::on_actionClamp_triggered(){
	ui->workspace->addNode(CLAMP_G);
}
void MainWindow::on_actionBitmap_triggered(){
	ui->workspace->addNode(BITMAP_G);
}
void MainWindow::on_actionSin_triggered(){
	ui->workspace->addNode(SIN_G);
}
void MainWindow::on_actionCos_triggered(){
	ui->workspace->addNode(COS_G);
}
void MainWindow::on_actionMin_triggered(){
	ui->workspace->addNode(MIN_G);
}
void MainWindow::on_actionMax_triggered(){
	ui->workspace->addNode(MAX_G);
}
void MainWindow::on_actionRatio_triggered(){
	ui->workspace->addNode(RATIO_G);
	ui->actionRatio->setEnabled(false);
	ui->toolBox->ratio->setEnabled(false);
}
void MainWindow::on_actionComplex_triggered(){
	ui->workspace->addNode(CPLX_G);
}
void MainWindow::on_actionHSV_triggered(){
	ui->workspace->addNode(HSV_G);
}
void MainWindow::on_actionRGB_triggered(){
	ui->workspace->addNode(RGB_G);
}
