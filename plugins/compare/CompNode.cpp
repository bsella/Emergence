#include "CompNode.h"

CompNode::CompNode(const std::string &type):Node(type,50,50,QColor(255,180,180),2){}

GTNode::GTNode():CompNode("gt"){}
LTNode::LTNode():CompNode("lt"){}
EQNode::EQNode():CompNode("eq"){}
NENode::NENode():CompNode("ne"){}

void GTNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	drawIcon(painter,":/gt.png");
}
void LTNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	drawIcon(painter,":/lt.png");
}
void EQNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	drawIcon(painter,":/eq.png");
}
void NENode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	drawIcon(painter,":/ne.png");
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
