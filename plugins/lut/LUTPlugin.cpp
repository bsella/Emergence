#include "LUTPlugin.h"
#include "PaletteNode.h"

void LUTPlugin::updateUI(Ui::MainWindow* ui) const{
	QAction* lutAction= new QAction("LUT");

	Workspace* ws=(Workspace*)ui->workspace->scene();
	connect(lutAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("lut"));});

	ui->menuInsert->addAction(lutAction);
}

void LUTPlugin::init()const{
	Node::makeNodeMethods["lut"] = &LUTNode::makeNode;
	NodeBox::addTool("lut","LUT","Color");
}
