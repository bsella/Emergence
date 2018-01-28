#include "include/IfGate.h"

IfGate::IfGate():Gate(IF_G,50,100,QColor(180,180,255),3){}

void IfGate::paint(QPainter* painter,
               const QStyleOptionGraphicsItem*option,
               QWidget*widget){
	Gate::paint(painter,option,widget);
    QRectF rect=boundingRect();
    rect.setLeft(rect.left()+socketSize); rect.setRight(rect.right()-socketSize);
    painter->drawLine(rect.center()+QPointF(rect.width()/2,0),rect.center()+QPointF(rect.width()/2+socketSize,0));
    painter->setPen(QPen(Qt::black,1));
    painter->drawText(rect.topLeft()+QPointF(8,rect.height()/4.0+4),"THEN");
    painter->drawText(rect.topLeft()+QPointF(8,2*rect.height()/4.0+4),"IF");
    painter->drawText(rect.topLeft()+QPointF(8,3*rect.height()/4.0+4),"ELSE");
}

data_t IfGate::eval()const{
    return iGates[1]->eval()? iGates[0]->eval() : iGates[2]->eval();
}
