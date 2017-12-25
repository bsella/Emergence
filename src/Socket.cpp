#include "lib/Socket.h"
#include <iostream>

Socket::Socket(unsigned i, double y, QGraphicsItem *parent):rank(i),iy(y),QGraphicsItem(parent){
	setZValue(parent->zValue()+1);
	line = new QGraphicsLineItem(this);
	line->setPos(5,0);
	setPos(-5,y);
	setAcceptedMouseButtons(Qt::LeftButton);
}

QRectF Socket::boundingRect()const{
	return QRectF(-headSize,-headSize,headSize*2,headSize*2);
}

void Socket::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
	painter->setRenderHint(QPainter::Antialiasing);
	painter->drawEllipse(boundingRect().center(),headSize,headSize);
	line->update();
}

#include <QApplication>
void Socket::mouseMoveEvent(QGraphicsSceneMouseEvent*){
//    QGraphicsItem* p= parentItem();
//    this->setPos(event->scenePos()-p->pos()- boundingRect().center());
//    line->setLine(0,0,-x()-5,-y()+iy);
	QDrag *drag = new QDrag(parentObject());
	QMimeData *mime = new QMimeData;
	drag->setMimeData(mime);
	mime->setParent(parentObject());
	mime->setData("rank",QByteArray::number(rank));
	drag->exec();
}
void Socket::mousePressEvent(QGraphicsSceneMouseEvent*){
	//QDrag *drag= new QDrag;
}
void Socket::mouseReleaseEvent(QGraphicsSceneMouseEvent* ){
	if(collidingItems().count()){
		//QApplication::beep();
	}
}
