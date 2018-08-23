#include "ComparePlugin.h"

void ComparePlugin::updateUI(Ui::MainWindow*ui) const{
	QMenu* compMenu = new QMenu("Compare",ui->menuInsert);
	ui->menuInsert->addAction(compMenu->menuAction());
	QAction* gtAction= new QAction(QIcon(":/gt.png"), "Greater Than");
	QAction* ltAction= new QAction(QIcon(":/lt.png"), "Less Than");
	QAction* eqAction= new QAction(QIcon(":/eq.png"), "Equal");
	QAction* neAction= new QAction(QIcon(":/ne.png"), "Not Equal");

	Workspace* ws= (Workspace*)ui->workspace->scene();
	connect(gtAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("gt"));});
	connect(ltAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("lt"));});
	connect(eqAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("eq"));});
	connect(neAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("ne"));});

	compMenu->addAction(gtAction);
	compMenu->addAction(ltAction);
	compMenu->addAction(eqAction);
	compMenu->addAction(neAction);

	ui->toolBox->addTool("gt","Greater Than",QIcon(":/gt.png"),"Compare");
	ui->toolBox->addTool("lt","Less Than",QIcon(":/lt.png"),"Compare");
	ui->toolBox->addTool("eq","Equal",QIcon(":/eq.png"),"Compare");
	ui->toolBox->addTool("ne","Not Equal",QIcon(":/ne.png"),"Compare");
}

void ComparePlugin::init()const{
	Node::makeNodeMethods["gt"] = &GTNode::makeNode;
	Node::makeNodeMethods["lt"] = &LTNode::makeNode;
	Node::makeNodeMethods["eq"] = &EQNode::makeNode;
	Node::makeNodeMethods["ne"] = &NENode::makeNode;
}
