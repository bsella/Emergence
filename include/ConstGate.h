#ifndef CONSTGATE_H
#define CONSTGATE_H

#include "Gate.h"
#include <QColorDialog>
#include <QInputDialog>

class ConstGate:public Gate{
public:
	ConstGate(double v);
	ConstGate(uint v);
private:
	data_t _v;
	ConstGate()=delete;
	inline data_t eval()const{return _v;}
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*widget);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
	friend class Workspace;
private slots:
	void changeColor();
	void changeNumber();
};

#endif
