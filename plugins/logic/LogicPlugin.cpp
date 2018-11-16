#include "LogicPlugin.h"
#include "LogicNode.h"

void LogicPlugin::updateUI(Ui::MainWindow* ui) const{
	QMenu* logicMenu = new QMenu("Logic",ui->menuInsert);
	ui->menuInsert->addAction(logicMenu->menuAction());
	QAction* andAction= new QAction(QIcon(":/and.png"), "And");
	QAction* orAction= new QAction(QIcon(":/or.png"), "Or");
	QAction* xorAction= new QAction(QIcon(":/xor.png"), "Xor");
	QAction* notAction= new QAction(QIcon(":/not.png"), "Not");

	Workspace* ws=(Workspace*)ui->workspace->scene();
	connect(andAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("and"));});
	connect(orAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("or"));});
	connect(xorAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("xor"));});
	connect(notAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("not"));});

	logicMenu->addAction(andAction);
	logicMenu->addAction(orAction);
	logicMenu->addAction(xorAction);
	logicMenu->addAction(notAction);

}

void LogicPlugin::init()const{
	Node::makeNodeBinTextMethods["and"] = {&ANDNode::makeNode,&ANDNode::makeNode};
	Node::makeNodeBinTextMethods["or"] =  {&ORNode::makeNode ,&ORNode::makeNode };
	Node::makeNodeBinTextMethods["xor"] = {&XORNode::makeNode,&XORNode::makeNode};
	Node::makeNodeBinTextMethods["not"] = {&NOTNode::makeNode,&NOTNode::makeNode};

	NodeBox::addTool("and","And",QIcon(":/and.png"),"Logic");
	NodeBox::addTool("or","Or",QIcon(":/or.png"),"Logic");
	NodeBox::addTool("xor","Xor",QIcon(":/xor.png"),"Logic");
	NodeBox::addTool("not","Not",QIcon(":/not.png"),"Logic");
}
