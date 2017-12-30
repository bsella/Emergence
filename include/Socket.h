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
	//void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
private:
	unsigned rank;
	static const int headSize=5;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
	double iy;
	void mouseMoveEvent(QGraphicsSceneMouseEvent*);
	void mousePressEvent(QGraphicsSceneMouseEvent*);
	//QGraphicsLineItem *line;
};

#endif // SOCKET_H
