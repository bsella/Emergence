#include "IoPlugin.h"

void IoPlugin::updateUI(QMenu* insertMenu, NodeBox*, Workspace*ws) const{
	QMenu* ioMenu = new QMenu("Io",insertMenu);
	insertMenu->addAction(ioMenu->menuAction());
	QAction* xAction= new QAction("X");
	QAction* yAction= new QAction("Y");
	QAction* ratioAction= new QAction("Ratio");
	QAction* outAction= new QAction("Render");

	connect(xAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("x"));});
	connect(yAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("y"));});
	connect(ratioAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("ratio"));});
	connect(outAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("out"));});

	ioMenu->addAction(xAction);
	ioMenu->addAction(yAction);
	ioMenu->addAction(ratioAction);
	ioMenu->addAction(outAction);
}

void IoPlugin::addNodes()const{
	QApplication::beep();
	Node::makeNodeMethods["x"] = &XNode::makeNode;
//	Node::makeNodeMethods["y"] = &YNode::makeNode;
//	Node::makeNodeMethods["ratio"]= &RatioNode::makeNode;
//	Node::makeNodeMethods["out"]= &OutputNode::makeNode;
}
