#include "lib/PixelGate.h"

void PixelGate::update(double i){
    v=i;
}
data_t PixelGate::eval()const{
    return v;
}
PixelGate::PixelGate():FuncGate(70,50,Qt::lightGray){}

void PixelGate::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
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

void PixelXGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    PixelGate::paint(painter,option,widget);
    QRectF rect=boundingRect();
    painter->drawText(rect.center()+QPointF(-5,3),"X");
}
void PixelYGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    PixelGate::paint(painter,option,widget);
    QRectF rect=boundingRect();
    painter->drawText(rect.x()+rect.width()/2-5,rect.y()+rect.height()/2+3,"Y");
}
