#include "lib/IfGate.h"

IfGate::IfGate():FuncGate(50,100,QColor(180,180,255),3){}

void IfGate::paint(QPainter* painter,
               const QStyleOptionGraphicsItem*option,
               QWidget*widget){
    FuncGate::paint(painter,option,widget);
    QRectF rect=boundingRect();
    rect.setLeft(rect.left()+socketSize); rect.setRight(rect.right()-socketSize);
    painter->drawLine(rect.center()+QPointF(rect.width()/2,0),rect.center()+QPointF(rect.width()/2+socketSize,0));
    painter->setPen(QPen(Qt::black,1));
    painter->drawText(rect.topLeft()+QPointF(8,rect.height()/4.0+4),"THEN");
    painter->drawText(rect.topLeft()+QPointF(8,2*rect.height()/4.0+4),"IF");
    painter->drawText(rect.topLeft()+QPointF(8,3*rect.height()/4.0+4),"ELSE");
}

data_t IfGate::eval()const{
    if(input[1]->eval())
        return input[0]->eval();
    return input[2]->eval();
}
