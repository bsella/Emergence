#include "LogicPlugin.h"

void LogicPlugin::updateUI(QMenu* insertMenu, NodeBox*box, Workspace*ws) const{
	QMenu* logicMenu = new QMenu("Logic",insertMenu);
	insertMenu->addAction(logicMenu->menuAction());
	QAction* andAction= new QAction(QIcon(":/and.png"), "And");
	QAction* orAction= new QAction(QIcon(":/or.png"), "Or");
	QAction* xorAction= new QAction(QIcon(":/xor.png"), "Xor");
	QAction* notAction= new QAction(QIcon(":/not.png"), "Not");

	connect(andAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("and"));});
	connect(orAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("or"));});
	connect(xorAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("xor"));});
	connect(notAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("not"));});

	logicMenu->addAction(andAction);
	logicMenu->addAction(orAction);
	logicMenu->addAction(xorAction);
	logicMenu->addAction(notAction);

	box->addTool("and","And",QIcon(":/and.png"),"Logic");
	box->addTool("or","Or",QIcon(":/or.png"),"Logic");
	box->addTool("xor","Xor",QIcon(":/xor.png"),"Logic");
	box->addTool("not","Not",QIcon(":/not.png"),"Logic");
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
