#ifndef MATHGATE_H
#define MATHGATE_H

#include "FuncGate.h"
#include <QtMath>

class MathGate:public FuncGate{
protected:
	MathGate(unsigned n);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)=0;
};

class ADDGate:public MathGate{
public:
	ADDGate();
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class SUBGate:public MathGate{
public:
	SUBGate();
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class MULGate:public MathGate{
public:
	MULGate();
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class DIVGate:public MathGate{
public:
	DIVGate();
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class NEGGate:public MathGate{
public:
	NEGGate();
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class SQRTGate:public MathGate{
public:
	SQRTGate();
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // MATHGATE_H
