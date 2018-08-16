#ifndef REALNODE_H
#define REALNODE_H

#include "Node.h"
#include <QColorDialog>
#include <QInputDialog>

class RealNode:public Node{
public:
	RealNode(double v=0);
private:
	inline data_t kernel()const{return cache;}
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*widget);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
private slots:
	void changeNumber();
};

#endif
