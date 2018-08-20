#include "ConditionPlugin.h"

void ConditionPlugin::updateUI(QMenu* insertMenu, NodeBox*box, Workspace*ws) const{
	QAction* ifAction= new QAction(QIcon(":/if.png"),"Condition");

	connect(ifAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("if"));});

	insertMenu->addAction(ifAction);

	box->addTool("if","Condition",QIcon(":/if.png"));
}

void ConditionPlugin::addNodes()const{
	Node::makeNodeMethods["if"] = &IfNode::makeNode;
}
