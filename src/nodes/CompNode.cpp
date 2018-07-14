#include "nodes/CompNode.h"

CompNode::CompNode(unsigned i):Node(i,50,50,QColor(255,180,180),2){}

GTNode::GTNode():CompNode(GT_G){}
LTNode::LTNode():CompNode(LT_G){}
EQNode::EQNode():CompNode(EQ_G){}
NENode::NENode():CompNode(NE_G){}

void GTNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	drawIcon(painter,":/icons/greater_than.png");
}
void NENode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	drawIcon(painter,":/icons/not_equal.png");
}
void EQNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	drawIcon(painter,":/icons/equal.png");
}
void LTNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	drawIcon(painter,":/icons/less_than.png");
}
data_t GTNode::kernel()const{
	return iNodes[0]->eval() > iNodes[1]->eval();
}

data_t LTNode::kernel()const{
	return iNodes[0]->eval() < iNodes[1]->eval();
}

data_t EQNode::kernel()const{
	return iNodes[0]->eval() == iNodes[1]->eval();
}

data_t NENode::kernel()const{
	return iNodes[0]->eval() != iNodes[1]->eval();
}
