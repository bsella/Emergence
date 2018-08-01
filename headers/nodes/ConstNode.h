#ifndef CONSTNODE_H
#define CONSTNODE_H

#include "Node.h"
#include <QColorDialog>
#include <QInputDialog>

class ConstNode:public Node{
public:
	ConstNode(double v=0);
	ConstNode(data_t::color v);
private:
	ConstNode()=delete;
	inline data_t kernel()const{return cache;}
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*widget);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
	friend class Workspace;
private slots:
	void changeColor();
	void changeNumber();
};

#endif
