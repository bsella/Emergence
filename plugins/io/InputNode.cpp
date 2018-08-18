#include "InputNode.h"

InputNode::InputNode(const QString& type):Node(type,70,50,Qt::lightGray){}
XNode::XNode():InputNode("x"){}
YNode::YNode():InputNode("y"){}
RatioNode::RatioNode():Node("ratio",70,50,Qt::lightGray){
	constant=true;
	connect(&sm,SIGNAL(updateRatio()),this,SLOT(updateVal()));
}
RatioNode::~RatioNode(){
	disconnect(&sm,SIGNAL(updateRatio()),this,SLOT(updateVal()));
}

void InputNode::paint(QPainter *painter, const QStyleOptionGraphicsItem*option, QWidget*widget){
	Node::paint(painter,option,widget);
}

void XNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	InputNode::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.center()+QPointF(-5,3),"X");
}
void YNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	InputNode::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.center()+QPoint(-5,3),"Y");
}

void RatioNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.x()+rect.width()/3,rect.y()+rect.height()/2+3,"W/H");
}

