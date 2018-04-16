#include "include/nodes/PixelNode.h"

void PixelNode::update(double i){
	val=i;
	updateOutputVal();
}
void RatioNode::update(unsigned x, unsigned y){
	val=double(x)/y;
	updateOutputVal();
}
void PixelNode::removeNode(){
	Node::removeNode();
	emit deleted();
}
PixelNode::PixelNode(unsigned i):Node(i,70,50,Qt::lightGray){
	validVal=true;
}
PixelXNode::PixelXNode():PixelNode(X_G){}
PixelYNode::PixelYNode():PixelNode(Y_G){}
RatioNode::RatioNode():PixelNode(RATIO_G){}

void PixelNode::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
	QRectF rect=boundingRect();
	rect.setRight(rect.right()-socketSize);
	painter->setRenderHint(QPainter::Antialiasing);
	QPainterPath path;
	path.addRoundedRect(rect, 10, 10);
	painter->setPen(pen);
	painter->fillPath(path, Qt::lightGray);
	painter->drawPath(path);
	painter->drawLine(rect.center()+QPointF(rect.width()/2,0),rect.center()+QPointF(rect.width()/2+socketSize,0));
}

void PixelXNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	PixelNode::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.center()+QPointF(-5,3),"X");
}
void PixelYNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	PixelNode::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.x()+rect.width()/2-5,rect.y()+rect.height()/2+3,"Y");
}

void RatioNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	PixelNode::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.x()+rect.width()/3,rect.y()+rect.height()/2+3,"X/Y");
}
