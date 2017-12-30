#ifndef PXYGATE_H
#define PXYGATE_H

#include "FuncGate.h"

class PixelGate:public FuncGate{
public:
		void update(double i);
		data_t eval()const;
protected:
		PixelGate();
		virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
private:
		double v;
		void removeGate();
};

class PixelXGate:public PixelGate{
public:
		void paint(QPainter* painter,
									 const QStyleOptionGraphicsItem* option,
									 QWidget* widget);
};

class PixelYGate:public PixelGate{
public:
		void paint(QPainter* painter,
									 const QStyleOptionGraphicsItem* option,
									 QWidget* widget);
};

#endif
