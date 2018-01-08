#ifndef MATHGATE_H
#define MATHGATE_H

#include "Gate.h"
#include <QtMath>

class MathGate:public Gate{
protected:
	MathGate(unsigned n, unsigned w=50, unsigned h=50);
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

class ABSGate:public MathGate{
public:
	ABSGate();
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class LERPGate:public MathGate{
public:
	LERPGate();
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class CLAMPGate:public MathGate{
public:
	CLAMPGate();
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // MATHGATE_H
