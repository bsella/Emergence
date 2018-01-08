#ifndef GATE_H
#define GATE_H
#include <vector>

#include <QGraphicsObject>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QGraphicsScene>
#include <QMenu>

#include "data_t.h"
#include "Socket.h"

class Gate: public QGraphicsObject{
	Q_OBJECT
public:
	unsigned int width, height;
	virtual data_t eval()const=0;
	operator bool();
signals:
	void notifyRA();
	void deleted();
private slots:
	void disconnectGate(unsigned rank);
protected slots:
	virtual void removeGate();
protected:
	QMenu *menu=nullptr;
	QColor color;
	Gate(unsigned w=50, unsigned h=50, QColor c=Qt::white,uint n=0, bool spec=false);
	virtual void paint(QPainter* painter,
			   const QStyleOptionGraphicsItem* option,
			   QWidget* widget);
	QPen pen;
	QRectF boundingRect()const;
	uint nbArgs;
	static const int socketSize=5;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	std::vector<Gate*> iGates;          //INPUT GATES
	std::vector<QGraphicsLineItem*> iLines;
	std::list<std::pair<Gate*,uint>> oConnections;
	std::vector<Socket*> sockets;
	virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	void dropEvent(QGraphicsSceneDragDropEvent *event);
	void connectGate(Gate *g, unsigned i);
private:
	bool special;
};

#endif
