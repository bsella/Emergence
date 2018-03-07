#ifndef PALETTEGATE_H
#define PALETTEGATE_H

#include <include/Palette.h>
#include "Gate.h"

class LUTGate:public Gate{
public:
	LUTGate(const Palette& p);
private:
	void paint(QPainter* painter, const QStyleOptionGraphicsItem*option, QWidget*widget);
	data_t eval();
	Palette plt;
};

#endif
