#include "ImagePlugin.h"

void ImagePlugin::updateUI(Ui::MainWindow* ui) const{
	QAction* imageAction= new QAction(QIcon(":/image.png"),"Image");

	Workspace* ws= (Workspace*)ui->workspace->scene();
	connect(imageAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("img"));});

	ui->menuInsert->addAction(imageAction);

	ui->toolBox->addTool("img","Image",QIcon(":/image.png"));
}

void ImagePlugin::init()const{
	Node::makeNodeMethods["img"] = &BitmapNode::makeNode;
}
