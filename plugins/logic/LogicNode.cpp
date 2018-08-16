#include "LogicNode.h"

LogicNode::LogicNode(const QString &type, unsigned n):Node(type,50,50,QColor(255,180,180),n){}

ORNode::ORNode():LogicNode("or",2){}
ANDNode::ANDNode():LogicNode("and",2){}
XORNode::XORNode():LogicNode("xor",2){}
NOTNode::NOTNode():LogicNode("not",1){}

void ORNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option, widget);
	painter->drawText(boundingRect().center()-QPoint(10,-2),"OR");
}
void ANDNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option, widget);
	painter->drawText(boundingRect().center()-QPoint(12,-2),"AND");
}
void XORNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option, widget);
	painter->drawText(boundingRect().center()-QPoint(12,-2),"XOR");
}
void NOTNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option, widget);
	painter->drawText(boundingRect().center()-QPoint(12,-2),"NOT");
}

data_t ORNode::kernel()const{
	return iNodes[0]->eval() || iNodes[1]->eval();
}

data_t ANDNode::kernel()const{
	return iNodes[0]->eval() && iNodes[1]->eval();
}

data_t XORNode::kernel()const{
	return bool(bool(iNodes[0]->eval()) ^ bool(iNodes[1]->eval()));
}

data_t NOTNode::kernel()const{
	return !iNodes[0]->eval();
}
