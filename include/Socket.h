#ifndef SOCKET_H
#define SOCKET_H

#include<QCursor>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

class Socket: public QGraphicsItem{
public:
	Socket(unsigned i, double y, QGraphicsItem *parent);
	QRectF boundingRect() const;
	static const int socketSize=5;
private:
	unsigned rank;
	double iy;
	static const int headSize=8;
	QPen pen=QPen(Qt::black);
	QGraphicsLineItem *line=nullptr;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
	void hoverEnterEvent(QGraphicsSceneHoverEvent*);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
	void mouseMoveEvent(QGraphicsSceneMouseEvent*);
	void mousePressEvent(QGraphicsSceneMouseEvent*);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
	QGraphicsItem* collidesWithNode();
};

#endif // SOCKET_H
