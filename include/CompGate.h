#ifndef COMPGATE_H
#define COMPGATE_H

#include "Gate.h"

class CompGate:public Gate{
protected:
	CompGate(unsigned i);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*option, QWidget*widget)=0;
};

class GTGate:public CompGate{
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
	GTGate();
};

class LTGate:public CompGate{
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
	LTGate();
};

class EQGate:public CompGate{
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
	EQGate();
};

class NEGate:public CompGate{
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
	NEGate();
};

#endif
