#include "ColorPlugin.h"
#include "ColorNode.h"

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

}

void ColorPlugin::init()const{
	Node::makeNodeMethods["color"] = &ColorNode::makeNode;
	Node::makeNodeMethods["rgb"] = &RGBNode::makeNode;
	Node::makeNodeMethods["hsv"] = &HSVNode::makeNode;

	NodeBox::addTool("color","Color",QIcon(":/color.png"),"Color");
	NodeBox::addTool("rgb","RGB","Color");
	NodeBox::addTool("hsv","HSV","Color");
}
