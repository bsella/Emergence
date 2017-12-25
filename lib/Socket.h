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
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
	void mouseMoveEvent(QGraphicsSceneMouseEvent*);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
	void mousePressEvent(QGraphicsSceneMouseEvent*);
	QGraphicsLineItem *line;
	unsigned rank;
	double iy;
private:
	static const int headSize=5;
};

#endif // SOCKET_H
