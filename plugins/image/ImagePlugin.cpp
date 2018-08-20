#include "ImagePlugin.h"

void ImagePlugin::updateUI(QMenu* insertMenu, NodeBox*box, Workspace*ws) const{
	QAction* imageAction= new QAction(QIcon(":/image.png"),"Image");

	connect(imageAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("img"));});

	insertMenu->addAction(imageAction);

	box->addTool("img","Image",QIcon(":/image.png"));
}

void ImagePlugin::addNodes()const{
	Node::makeNodeMethods["img"] = &BitmapNode::makeNode;
}
