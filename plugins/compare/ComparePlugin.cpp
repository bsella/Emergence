#include "ComparePlugin.h"

void ComparePlugin::updateUI(QMenu* insertMenu, NodeBox*, Workspace*ws) const{
	QMenu* compMenu = new QMenu("Compare",insertMenu);
	insertMenu->addAction(compMenu->menuAction());
	QAction* gtAction= new QAction(QIcon(":/gt.png"), "Greater Than");
	QAction* ltAction= new QAction(QIcon(":/lt.png"), "Less Than");
	QAction* eqAction= new QAction(QIcon(":/eq.png"), "Equal");
	QAction* neAction= new QAction(QIcon(":/ne.png"), "Not Equal");

	connect(gtAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("gt"));});
	connect(ltAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("lt"));});
	connect(eqAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("eq"));});
	connect(neAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("ne"));});

	compMenu->addAction(gtAction);
	compMenu->addAction(ltAction);
	compMenu->addAction(eqAction);
	compMenu->addAction(neAction);
}

void ComparePlugin::addNodes()const{
	Node::makeNodeMethods["gt"] = &GTNode::makeNode;
	Node::makeNodeMethods["lt"] = &LTNode::makeNode;
	Node::makeNodeMethods["eq"] = &EQNode::makeNode;
	Node::makeNodeMethods["ne"] = &NENode::makeNode;
}
