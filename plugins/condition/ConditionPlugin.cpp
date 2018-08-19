#include "ConditionPlugin.h"

void ConditionPlugin::updateUI(QMenu* insertMenu, NodeBox*, Workspace*ws) const{
	QAction* ifAction= new QAction(QIcon(":/if.png"),"Condition");

	connect(ifAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("if"));});

	insertMenu->addAction(ifAction);
}

void ConditionPlugin::addNodes()const{
	Node::makeNodeMethods["if"] = &IfNode::makeNode;
}
