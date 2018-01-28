#ifndef LOGICGATE_H
#define LOGICGATE_H

#include "Gate.h"

class LogicGate:public Gate{
protected:
	LogicGate(unsigned i,unsigned n);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)=0;
};

class ORGate:public LogicGate{
public:
	ORGate();
private:
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class ANDGate:public LogicGate{
public:
	ANDGate();
private:
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class XORGate:public LogicGate{
public:
	XORGate();
private:
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class NOTGate:public LogicGate{
public:
	NOTGate();
private:
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif
