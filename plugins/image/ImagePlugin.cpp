#include "ImagePlugin.h"

void ImagePlugin::updateUI(QMenu* insertMenu, NodeBox*, Workspace*ws) const{
	QAction* imageAction= new QAction(QIcon(":/image.png"),"Image");

	connect(imageAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("img"));});

	insertMenu->addAction(imageAction);
}

void ImagePlugin::addNodes()const{
	Node::makeNodeMethods["img"] = &BitmapNode::makeNode;
}
