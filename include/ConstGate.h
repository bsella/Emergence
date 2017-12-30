#ifndef CONSTGATE_H
#define CONSTGATE_H

#include "FuncGate.h"
#include <QColorDialog>
#include <QInputDialog>

class ConstGate:public FuncGate{
public:
	ConstGate(double v);
	ConstGate(bool v);
	ConstGate(uint v);
	inline data_t eval()const{return _v;}
private:
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*widget);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
	data_t _v;
private slots:
	void changeColor();
	void changeNumber();
};

#endif
