#ifndef CONSTGATE_H
#define CONSTGATE_H

#include "Gate.h"
#include <QColorDialog>
#include <QInputDialog>

class ConstGate:public Gate{
public:
	ConstGate(double v);
	ConstGate(bool v);
	ConstGate(uint v);
	inline data_t eval()const{return _v;}
private:
	data_t _v;
	TypeEnum t;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*widget);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
private slots:
	void changeColor();
	void changeNumber();
};

#endif
