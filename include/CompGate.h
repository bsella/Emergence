#ifndef COMPGATE_H
#define COMPGATE_H

#include "Gate.h"

class CompGate:public Gate{
protected:
	CompGate();
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*option, QWidget*widget)=0;
};

class GTGate:public CompGate{
public:
	data_t eval()const;
private:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class LTGate:public CompGate{
public:
	data_t eval()const;
private:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class EQGate:public CompGate{
public:
	data_t eval()const;
private:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class NEGate:public CompGate{
public:
	data_t eval()const;
private:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif
