#include "MathPlugin.h"

void MathPlugin::updateUI(QMenu* insertMenu, NodeBox*, Workspace*ws) const{
	QMenu* mathMenu = new QMenu("Math",insertMenu);
	insertMenu->addAction(mathMenu->menuAction());
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

void MathPlugin::addNodes()const{
	Node::makeNodeMethods["add"] = &ADDNode::makeNode;
	Node::makeNodeMethods["sub"] = &SUBNode::makeNode;
	Node::makeNodeMethods["mul"] = &MULNode::makeNode;
	Node::makeNodeMethods["div"] = &DIVNode::makeNode;
	Node::makeNodeMethods["real"] = &RealNode::makeNode;
	Node::makeNodeMethods["cplx"] = &ComplexNode::makeNode;
	Node::makeNodeMethods["sqrt"] = &SQRTNode::makeNode;
	Node::makeNodeMethods["abs"] = &ABSNode::makeNode;
	Node::makeNodeMethods["neg"] = &NEGNode::makeNode;
	Node::makeNodeMethods["min"] = &MINNode::makeNode;
	Node::makeNodeMethods["max"] = &MAXNode::makeNode;
	Node::makeNodeMethods["pow"] = &POWNode::makeNode;
	Node::makeNodeMethods["log"] = &LOGNode::makeNode;
	Node::makeNodeMethods["sin"] = &SINNode::makeNode;
	Node::makeNodeMethods["cos"] = &COSNode::makeNode;
	Node::makeNodeMethods["lerp"] = &LERPNode::makeNode;
	Node::makeNodeMethods["clamp"] = &CLAMPNode::makeNode;
}
