#include "include/Socket.h"
#include <iostream>

Socket::Socket(unsigned i, double y, QGraphicsItem *parent):QGraphicsItem(parent),rank(i),iy(y){
	setZValue(parent->zValue()+1);
	setPos(-headSize-1,y);
	setAcceptedMouseButtons(Qt::LeftButton);
	setAcceptHoverEvents(true);
}

QRectF Socket::boundingRect()const{
	return QRectF(-headSize,-headSize,headSize*2+1,headSize*2+1);
}

void Socket::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
	painter->setPen(pen);
	painter->setRenderHint(QPainter::Antialiasing);
	painter->drawEllipse(boundingRect().center(),headSize,headSize);
}

void Socket::hoverEnterEvent(QGraphicsSceneHoverEvent *){
	pen.setWidth(2);
	update();
}

void Socket::hoverLeaveEvent(QGraphicsSceneHoverEvent *){
	pen.setWidth(1);
	update();
}

QGraphicsItem* Socket::collidesWithNode(){
	for(auto& i:collidingItems())
		if(i->data(0)=="node")
			return i;
	return nullptr;
}

void Socket::mouseMoveEvent(QGraphicsSceneMouseEvent*event){
	QGraphicsItem*i=collidesWithNode();
	if(i&&i->contains(event->scenePos()-i->scenePos())){
		QRectF r=i->boundingRect();
		parentItem()->setZValue(i->zValue()+1);
		setPos(i->pos()+QPoint(r.width()+Socket::headSize-1,r.height()/2)-parentItem()->pos());
	}else
		setPos(event->scenePos()- boundingRect().center()-parentObject()->pos());
	line->setLine(QLine({headSize,0},(parentObject()->scenePos()-scenePos()).toPoint()-QPoint(0,-iy)));
}

void Socket::mousePressEvent(QGraphicsSceneMouseEvent*){
	if(!line){
		line=scene()->addLine(headSize,0,headSize,0);
		line->setParentItem(this);
	}
}

void Socket::mouseReleaseEvent(QGraphicsSceneMouseEvent*){
	setPos(-headSize-1,iy);
	if(line){
		scene()->removeItem(line);
		line=nullptr;
	}
}
