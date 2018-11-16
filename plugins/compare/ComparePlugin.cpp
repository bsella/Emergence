#include "ComparePlugin.h"
#include "CompNode.h"

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

}

void ComparePlugin::init()const{
	Node::makeNodeBinTextMethods["gt"] = {&GTNode::makeNode,&GTNode::makeNode};
	Node::makeNodeBinTextMethods["lt"] = {&LTNode::makeNode,&LTNode::makeNode};
	Node::makeNodeBinTextMethods["eq"] = {&EQNode::makeNode,&EQNode::makeNode};
	Node::makeNodeBinTextMethods["ne"] = {&NENode::makeNode,&NENode::makeNode};

	NodeBox::addTool("gt","Greater Than",QIcon(":/gt.png"),"Compare");
	NodeBox::addTool("lt","Less Than",QIcon(":/lt.png"),"Compare");
	NodeBox::addTool("eq","Equal",QIcon(":/eq.png"),"Compare");
	NodeBox::addTool("ne","Not Equal",QIcon(":/ne.png"),"Compare");
}
