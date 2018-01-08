#ifndef PALETTEGATE_H
#define PALETTEGATE_H

#include "Palette.h"
#include "Gate.h"

class PaletteGate:public Gate{
public:
	PaletteGate(const Palette& p);
	data_t eval()const;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem*option, QWidget*widget);
private:
	Palette plt;
};

#endif
