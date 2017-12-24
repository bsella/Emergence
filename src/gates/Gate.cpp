#include "lib/Gate.h"
#include <iostream>

Gate::Gate(unsigned w, unsigned h, QColor c):width(w),height(h),color(c),pen(QPen(Qt::black,1)){
    setCursor(Qt::OpenHandCursor);
}

QRectF Gate::boundingRect()const{
    return QRectF(0,0,width+2*socketSize,height);
}

void Gate::paint(QPainter* painter, const QStyleOptionGraphicsItem*,QWidget*){
    QRectF rect=boundingRect();
    rect.setLeft(rect.left()+socketSize); rect.setRight(rect.right()-socketSize);
    painter->setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRoundedRect(rect, 10, 10);
    painter->setPen(pen);
    painter->fillPath(path, color);
    painter->drawPath(path);
}

void Gate::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if(event->button()==Qt::LeftButton){
        setCursor(Qt::ClosedHandCursor);
        pen.setWidth(2);
    }else
        setCursor(Qt::ArrowCursor);
}
void Gate::mouseReleaseEvent(QGraphicsSceneMouseEvent*){
    this->scene()->setSceneRect(this->scene()->itemsBoundingRect());
    setCursor(Qt::OpenHandCursor);
    setZValue(0);
    for(const auto& i: collidingItems())
        if(zValue()<= i->zValue())
            setZValue(i->zValue()+1);
    pen.setWidth(1);
}
void Gate::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(event->buttons()==Qt::LeftButton){
        setZValue(INT32_MAX);
        this->setPos(event->scenePos()- boundingRect().center());
    }
}
