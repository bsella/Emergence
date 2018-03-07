#ifndef COLORGATE_H
#define COLORGATE_H

#include <include/gates/Gate.h>
#include <include/data_t.h>

class ColorGate : public Gate{
protected:
	ColorGate(unsigned i);
	virtual void paint(QPainter* painter,
					const QStyleOptionGraphicsItem*option,
					QWidget *widget)=0;
};

class RGBGate : public ColorGate{
public:
	RGBGate();
private:
	data_t eval();
	void paint(QPainter* painter,
					const QStyleOptionGraphicsItem*option,
					QWidget *widget);
};

class HSVGate : public ColorGate{
public:
	HSVGate();
private:
	data_t eval();
	void paint(QPainter* painter,
					const QStyleOptionGraphicsItem*option,
					QWidget *widget);
};
#endif // COLORGATE_H
