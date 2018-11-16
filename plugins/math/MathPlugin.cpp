#include "MathPlugin.h"
#include "MathNode.h"
#include "RealNode.h"
#include "ComplexNode.h"

void MathPlugin::updateUI(Ui::MainWindow* ui) const{
	QMenu* mathMenu = new QMenu("Math",ui->menuInsert);
	ui->menuInsert->addAction(mathMenu->menuAction());
	QAction* addAction= new QAction(QIcon(":/add.png"),"Add");
	QAction* subAction= new QAction(QIcon(":/subtract.png"),"Subtract");
	QAction* mulAction= new QAction(QIcon(":/multiply.png"),"Multiply");
	QAction* divAction= new QAction(QIcon(":/divide.png"),"Divide");
	QAction* realAction= new QAction(QIcon(":/real.png"),"Real");
	QAction* complexAction= new QAction(QIcon(":/complex.png"),"Complex");
	QAction* sqrtAction= new QAction(QIcon(":/sqrt.png"),"Square Root");
	QAction* absAction= new QAction("Absolute Value");
	QAction* negAction= new QAction(QIcon(":/neg.png"),"Neg");
	QAction* minAction= new QAction("Min");
	QAction* maxAction= new QAction("Max");
	QAction* powAction= new QAction("Power");
	QAction* logAction= new QAction("Logarithm");
	QAction* sinAction= new QAction(QIcon(":/sin.png"),"Sin");
	QAction* cosAction= new QAction(QIcon(":/cos.png"),"Cos");
	QAction* lerpAction= new QAction("Linear Interpolation");
	QAction* clampAction= new QAction("Clamp");

	Workspace* ws=(Workspace*)ui->workspace->scene();
	connect(addAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("add"));});
	connect(subAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("sub"));});
	connect(mulAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("mul"));});
	connect(divAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("div"));});
	connect(realAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("real"));});
	connect(complexAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("cplx"));});
	connect(sqrtAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("sqrt"));});
	connect(absAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("abs"));});
	connect(negAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("neg"));});
	connect(minAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("min"));});
	connect(maxAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("max"));});
	connect(powAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("pow"));});
	connect(logAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("log"));});
	connect(sinAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("sin"));});
	connect(cosAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("cos"));});
	connect(lerpAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("lerp"));});
	connect(clampAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("clamp"));});

	mathMenu->addAction(addAction);
	mathMenu->addAction(subAction);
	mathMenu->addAction(mulAction);
	mathMenu->addAction(divAction);
	mathMenu->addAction(realAction);
	mathMenu->addAction(complexAction);
	mathMenu->addAction(sqrtAction);
	mathMenu->addAction(absAction);
	mathMenu->addAction(negAction);
	mathMenu->addAction(minAction);
	mathMenu->addAction(maxAction);
	mathMenu->addAction(powAction);
	mathMenu->addAction(logAction);
	mathMenu->addAction(sinAction);
	mathMenu->addAction(cosAction);
	mathMenu->addAction(lerpAction);
	mathMenu->addAction(clampAction);
}

void MathPlugin::init()const{
	Node::makeNodeBinTextMethods["add"] =  {&ADDNode::makeNode,&ADDNode::makeNode};
	Node::makeNodeBinTextMethods["sub"] =  {&SUBNode::makeNode,&SUBNode::makeNode};
	Node::makeNodeBinTextMethods["mul"] =  {&MULNode::makeNode,&MULNode::makeNode};
	Node::makeNodeBinTextMethods["div"] =  {&DIVNode::makeNode,&DIVNode::makeNode};
	Node::makeNodeBinTextMethods["real"] = {&RealNode::makeFromBin,&RealNode::makeFromText};
	Node::makeNodeBinTextMethods["cplx"] = {&ComplexNode::makeNode,&ComplexNode::makeNode};
	Node::makeNodeBinTextMethods["sqrt"] = {&SQRTNode::makeNode,&SQRTNode::makeNode};
	Node::makeNodeBinTextMethods["abs"] =  {&ABSNode::makeNode,&ABSNode::makeNode};
	Node::makeNodeBinTextMethods["neg"] =  {&NEGNode::makeNode,&NEGNode::makeNode};
	Node::makeNodeBinTextMethods["min"] =  {&MINNode::makeNode,&MINNode::makeNode};
	Node::makeNodeBinTextMethods["max"] =  {&MAXNode::makeNode,&MAXNode::makeNode};
	Node::makeNodeBinTextMethods["pow"] =  {&POWNode::makeNode,&POWNode::makeNode};
	Node::makeNodeBinTextMethods["log"] =  {&LOGNode::makeNode,&LOGNode::makeNode};
	Node::makeNodeBinTextMethods["sin"] =  {&SINNode::makeNode,&SINNode::makeNode};
	Node::makeNodeBinTextMethods["cos"] =  {&COSNode::makeNode,&COSNode::makeNode};
	Node::makeNodeBinTextMethods["lerp"] = {&LERPNode::makeNode,&LERPNode::makeNode};
	Node::makeNodeBinTextMethods["clamp"]= {&CLAMPNode::makeNode,&CLAMPNode::makeNode};

	NodeBox::addTool("add","Add",QIcon(":/add.png"),"Math");
	NodeBox::addTool("sub","Subtract",QIcon(":/subtract.png"),"Math");
	NodeBox::addTool("mul","Multiply",QIcon(":/multiply.png"),"Math");
	NodeBox::addTool("div","Divide",QIcon(":/divide.png"),"Math");
	NodeBox::addTool("real","Real",QIcon(":/real.png"),"Math");
	NodeBox::addTool("cplx","Complex",QIcon(":/complex.png"),"Math");
	NodeBox::addTool("sqrt","Square Root",QIcon(":/sqrt.png"),"Math");
	NodeBox::addTool("abs","Absolute Value","Math");
	NodeBox::addTool("neg","Negative",QIcon(":/neg.png"),"Math");
	NodeBox::addTool("min","Min","Math");
	NodeBox::addTool("max","Max","Math");
	NodeBox::addTool("pow","Power","Math");
	NodeBox::addTool("log","Logarithm","Math");
	NodeBox::addTool("sin","Sin",QIcon(":/sin.png"),"Math");
	NodeBox::addTool("cos","Cos",QIcon(":/cos.png"),"Math");
	NodeBox::addTool("lerp","Linear Interpolation","Math");
	NodeBox::addTool("clamp","Clamp","Math");
}
