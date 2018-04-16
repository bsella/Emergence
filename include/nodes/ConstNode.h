#ifndef CONSTNODE_H
#define CONSTNODE_H

#include "Node.h"
#include <QColorDialog>
#include <QInputDialog>

class ConstNode:public Node{
public:
	ConstNode(double v);
	ConstNode(uint v);
private:
	ConstNode()=delete;
	data_t eval();
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*widget);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
	friend class Workspace;
private slots:
	void changeColor();
	void changeNumber();
};

#endif
