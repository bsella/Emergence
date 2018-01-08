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
private:
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class SUBGate:public MathGate{
public:
	SUBGate();
private:
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class MULGate:public MathGate{
public:
	MULGate();
private:
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class DIVGate:public MathGate{
public:
	DIVGate();
private:
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class NEGGate:public MathGate{
public:
	NEGGate();
private:
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class SQRTGate:public MathGate{
public:
	SQRTGate();
private:
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class ABSGate:public MathGate{
public:
	ABSGate();
private:
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class LERPGate:public MathGate{
public:
	LERPGate();
private:
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class CLAMPGate:public MathGate{
public:
	CLAMPGate();
private:
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class SINGate:public MathGate{
public:
	SINGate();
private:
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class COSGate:public MathGate{
public:
	COSGate();
private:
	data_t eval()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // MATHGATE_H
