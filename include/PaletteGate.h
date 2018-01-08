#ifndef PALETTEGATE_H
#define PALETTEGATE_H

#include "Palette.h"
#include "Gate.h"

class PaletteGate:public Gate{
public:
	PaletteGate(const Palette& p);
private:
	void paint(QPainter* painter, const QStyleOptionGraphicsItem*option, QWidget*widget);
	data_t eval()const;
	Palette plt;
};

#endif
