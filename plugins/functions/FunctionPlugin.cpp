#include "FunctionPlugin.h"

#include "FunctionManager.h"

void FunctionPlugin::updateUI(Ui::MainWindow* ui) const{
	QAction* funcAction= new QAction("Function");

	Workspace* ws=(Workspace*)ui->workspace->scene();
	connect(funcAction,&QAction::triggered,ws,[=]{
		Function *f = FunctionManager::getFunction();
		if(f) ws->addNode(Node::nodeMalloc("fun",f));
	});

	ui->menuInsert->addAction(funcAction);

	ui->toolBox->addTool("fun","Function");

	QAction* fmAction= new QAction("Function Manager");
	connect(fmAction,SIGNAL(triggered(bool)),FunctionManager::instance(),SLOT(exec()));
	ui->menuTools->addAction(fmAction);
}

void FunctionPlugin::init()const{
	Node::makeNodeMethods["fun"] = &FunctionNode::makeNode;
}
