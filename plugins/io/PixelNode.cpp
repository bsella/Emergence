#include "nodes/PixelNode.h"

PixelNode::PixelNode(Type i):Node(i,70,50,Qt::lightGray){}
PixelXNode::PixelXNode():PixelNode(X_G){}
PixelYNode::PixelYNode():PixelNode(Y_G){}
RatioNode::RatioNode():Node(RATIO_G,70,50,Qt::lightGray){
	constant=true;
	connect(&sm,SIGNAL(updateRatio()),this,SLOT(updateVal()));
}
RatioNode::~RatioNode(){
	disconnect(&sm,SIGNAL(updateRatio()),this,SLOT(updateVal()));
}

void PixelNode::paint(QPainter *painter, const QStyleOptionGraphicsItem*option, QWidget*widget){
	Node::paint(painter,option,widget);
}

void PixelXNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	PixelNode::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.center()+QPointF(-5,3),"X");
}
void PixelYNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	PixelNode::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.center()+QPoint(-5,3),"Y");
}

void RatioNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.x()+rect.width()/3,rect.y()+rect.height()/2+3,"W/H");
}
