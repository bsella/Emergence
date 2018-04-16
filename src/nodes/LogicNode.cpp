#include "include/nodes/LogicNode.h"

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

data_t ORNode::eval(){
	if(validVal) return val;
	val= iNodes[0]->eval() || iNodes[1]->eval();
	validVal=true;
	return val;
}

data_t ANDNode::eval(){
	if(validVal) return val;
	val= iNodes[0]->eval() && iNodes[1]->eval();
	validVal=true;
	return val;
}

data_t XORNode::eval(){
	if(validVal) return val;
	val= iNodes[0]->eval() ^ iNodes[1]->eval();
	validVal=true;
	return val;
}

data_t NOTNode::eval(){
	if(validVal) return val;
	val= !iNodes[0]->eval();
	validVal=true;
	return val;
}
