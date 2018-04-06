#ifndef PXYGATE_H
#define PXYGATE_H

#include "Gate.h"

class PixelGate:public Gate{
public:
		void update(double i);
protected:
		PixelGate(unsigned i);
		virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
private:
		inline data_t eval(){return val;}
		void removeGate();
};

class PixelXGate:public PixelGate{
		void paint(QPainter* painter,
				   const QStyleOptionGraphicsItem* option,
				   QWidget* widget);
public:
		PixelXGate();
};

class PixelYGate:public PixelGate{
	void paint(QPainter* painter,
				const QStyleOptionGraphicsItem* option,
				QWidget* widget);
public:
	PixelYGate();
};

class RatioGate:public PixelGate{
	void paint(QPainter* painter,
				const QStyleOptionGraphicsItem* option,
				QWidget* widget);
public:
	RatioGate();
	void update(unsigned x, unsigned y);
};

#endif
