#include "LUTPlugin.h"

void LUTPlugin::updateUI(QMenu* insertMenu, NodeBox*box, Workspace*ws) const{
	QAction* lutAction= new QAction("LUT");

	connect(lutAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("lut"));});

	insertMenu->addAction(lutAction);

	box->addTool("lut","LUT","Color");
}

void LUTPlugin::addNodes()const{
	Node::makeNodeMethods["lut"] = &LUTNode::makeNode;
}
