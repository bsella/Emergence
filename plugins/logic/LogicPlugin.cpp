#include "LogicPlugin.h"

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

	ui->toolBox->addTool("and","And",QIcon(":/and.png"),"Logic");
	ui->toolBox->addTool("or","Or",QIcon(":/or.png"),"Logic");
	ui->toolBox->addTool("xor","Xor",QIcon(":/xor.png"),"Logic");
	ui->toolBox->addTool("not","Not",QIcon(":/not.png"),"Logic");
}

void LogicPlugin::init()const{
	Node::makeNodeMethods["and"] = &ANDNode::makeNode;
	Node::makeNodeMethods["or"] = &ORNode::makeNode;
	Node::makeNodeMethods["xor"] = &XORNode::makeNode;
	Node::makeNodeMethods["not"] = &NOTNode::makeNode;
}
