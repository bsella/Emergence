#include "nodes/LogicNode.h"

LogicNode::LogicNode(unsigned i,unsigned n):Node(i,50,50,QColor(255,180,180),n){}

ORNode::ORNode():LogicNode(OR_G,2){}
ANDNode::ANDNode():LogicNode(AND_G,2){}
XORNode::XORNode():LogicNode(XOR_G,2){}
NOTNode::NOTNode():LogicNode(NOT_G,1){}

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
