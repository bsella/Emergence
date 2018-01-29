#include "include/Socket.h"
#include <iostream>

Socket::Socket(unsigned i, double y, QGraphicsItem *parent):rank(i),iy(y),QGraphicsItem(parent){
	setZValue(parent->zValue()+1);
	setPos(-5,y);
	setAcceptedMouseButtons(Qt::LeftButton);
}

QRectF Socket::boundingRect()const{
	return QRectF(-headSize,-headSize,headSize*2,headSize*2);
}

void Socket::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
	painter->setRenderHint(QPainter::Antialiasing);
	painter->drawEllipse(boundingRect().center(),headSize,headSize);
}

void Socket::mouseMoveEvent(QGraphicsSceneMouseEvent*){
	QDrag *drag = new QDrag(parentObject());
	QMimeData *mime = new QMimeData;
	drag->setMimeData(mime);
	mime->setParent(parentObject());
	mime->setData("rank",QByteArray::number(rank));
	mime->setData("socket",QByteArray::number(1));
	drag->exec();
	parentObject()->setAcceptDrops(true);
	delete mime;
	delete drag;
}

void Socket::mousePressEvent(QGraphicsSceneMouseEvent*){}
