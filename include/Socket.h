#ifndef SOCKET_H
#define SOCKET_H

#include <QMimeData>
#include <QDrag>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

class Socket: public QGraphicsItem{
public:
	Socket(unsigned i, double y, QGraphicsItem *parent);
	QRectF boundingRect() const;
private:
	unsigned rank;
	double iy;
	static const int headSize=5;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
	void mouseMoveEvent(QGraphicsSceneMouseEvent*);
	void mousePressEvent(QGraphicsSceneMouseEvent*);
};

#endif // SOCKET_H
