#include "FunctionPlugin.h"

#include "FunctionNode.h"
#include "FunctionManager.h"

void FunctionPlugin::updateUI(Ui::MainWindow* ui) const{
	QAction* funcAction= new QAction("Function");

	Workspace* ws=(Workspace*)ui->workspace->scene();
	connect(funcAction,&QAction::triggered,ws,[=]{
		Function* f= FunctionManager::getFunction();
		if(f){
			std::istringstream in(std::to_string(FunctionManager::indexOf(f)));
			ws->addNode(Node::nodeMalloc("fun",in));
		}
	});

	ui->menuInsert->addAction(funcAction);

	QAction* fmAction= new QAction("Function Manager");
	connect(fmAction,SIGNAL(triggered(bool)),FunctionManager::instance(),SLOT(exec()));
	ui->menuTools->addAction(fmAction);
}

void FunctionPlugin::init()const{
	Node::makeNodeMethods["fun"] = &FunctionNode::makeNode;
	Node::makeNodeMethods["fin"] = &Function::FunctionInputNode::makeNode;
	Node::makeNodeMethods["fout"] = &Function::FunctionOutputNode::makeNode;
	NodeBox::addTool("fun","Function");
}

void FunctionPlugin::save(std::ostream &out)const{
	int tmp= FunctionManager::count();
	out << tmp << '\n';
	for(int i=0; i<tmp;i++)
		out<<*FunctionManager::functionAt(i);
}

void FunctionPlugin::load(std::istream &in) const{
	FunctionManager::clear();
	int tmp;
	in>>tmp;
	for(int i=0;i<tmp;i++)
		in >> *FunctionManager::instance();
}
