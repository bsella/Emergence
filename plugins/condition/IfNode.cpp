#include "IfNode.h"

#include <QPainter>

IfNode::IfNode():Node("if",50,100,QColor(180,180,255),3){}

void IfNode::paint(QPainter* painter,
				const QStyleOptionGraphicsItem*option,
				QWidget*widget){
	Node::paint(painter,option,widget);
	painter->setPen(QPen(Qt::black,1));
	QRectF rect=boundingRect();
	painter->drawText(rect.topLeft()+QPointF(8,rect.height()/4.0+4),"THEN");
	painter->drawText(rect.topLeft()+QPointF(8,2*rect.height()/4.0+4),"IF");
	painter->drawText(rect.topLeft()+QPointF(8,3*rect.height()/4.0+4),"ELSE");
}

data_t IfNode::kernel()const{
	return iNodes[1]->eval()? iNodes[0]->eval() : iNodes[2]->eval();
}
