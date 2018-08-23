#include "ColorPlugin.h"

void ColorPlugin::updateUI(Ui::MainWindow *ui) const{
	QMenu* colorMenu = new QMenu("Color",ui->menuInsert);
	ui->menuInsert->addAction(colorMenu->menuAction());
	QAction* colorAction= new QAction(QIcon(":/color.png"),"Color");
	QAction* rgbAction= new QAction("RGB");
	QAction* hsvAction= new QAction("HSV");

	Workspace* ws= (Workspace*)ui->workspace->scene();
	connect(colorAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("color"));});
	connect(rgbAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("rgb"));});
	connect(hsvAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("hsv"));});

	colorMenu->addAction(colorAction);
	colorMenu->addAction(rgbAction);
	colorMenu->addAction(hsvAction);

	ui->toolBox->addTool("color","Color",QIcon(":/color.png"),"Color");
	ui->toolBox->addTool("rgb","RGB","Color");
	ui->toolBox->addTool("hsv","HSV","Color");
}

void ColorPlugin::init()const{
	Node::makeNodeMethods["color"] = &ColorNode::makeNode;
	Node::makeNodeMethods["rgb"] = &RGBNode::makeNode;
	Node::makeNodeMethods["hsv"] = &HSVNode::makeNode;
}
