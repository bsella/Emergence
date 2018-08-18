#include "LogicPlugin.h"

void LogicPlugin::updateUI(QMenu* insertMenu, NodeBox*, Workspace*ws) const{
	QMenu* logicMenu = new QMenu("Logic",insertMenu);
	insertMenu->addAction(logicMenu->menuAction());
	QAction* andAction= new QAction("And");
	QAction* orAction= new QAction("Or");
	QAction* xorAction= new QAction("Xor");
	QAction* notAction= new QAction("Not");

	connect(andAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("and"));});
	connect(orAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("or"));});
	connect(xorAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("xor"));});
	connect(notAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("not"));});

	logicMenu->addAction(andAction);
	logicMenu->addAction(orAction);
	logicMenu->addAction(xorAction);
	logicMenu->addAction(notAction);
}

void LogicPlugin::addNodes()const{
	Node::makeNodeMethods["and"] = &ANDNode::makeNode;
	Node::makeNodeMethods["or"] = &ORNode::makeNode;
	Node::makeNodeMethods["xor"] = &XORNode::makeNode;
	Node::makeNodeMethods["not"] = &NOTNode::makeNode;

//	Node::knownTypes.append("and");
//	Node::knownTypes.append("or");
//	Node::knownTypes.append("xor");
//	Node::knownTypes.append("not");
}
