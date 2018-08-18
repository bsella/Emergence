#include "LUTPlugin.h"

void LUTPlugin::updateUI(QMenu* insertMenu, NodeBox*, Workspace*ws) const{
	QAction* lutAction= new QAction("LUT");

	connect(lutAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("lut"));});

	insertMenu->addAction(lutAction);
}

void LUTPlugin::addNodes()const{
	Node::makeNodeMethods["lut"] = &LUTNode::makeNode;
}
