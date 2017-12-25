#ifndef COMPGATE_H
#define COMPGATE_H

#include "FuncGate.h"

class LogicGate:public FuncGate{
protected:
	LogicGate(unsigned n);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)=0;
};

class ORGate:public LogicGate{
public:
	ORGate();
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class ANDGate:public LogicGate{
public:
	ANDGate();
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class XORGate:public LogicGate{
public:
	XORGate();
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class NANDGate:public LogicGate{
public:
	NANDGate();
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class NORGate:public LogicGate{
public:
	NORGate();
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class XNORGate:public LogicGate{
public:
	XNORGate();
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class NOTGate:public LogicGate{
public:
	NOTGate();
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif
