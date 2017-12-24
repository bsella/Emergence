#ifndef PALETTEGATE_H
#define PALETTEGATE_H

#include "Palette.h"
#include "FuncGate.h"

class PaletteGate:public FuncGate{
public:
	PaletteGate(const Palette& p);
    data_t eval()const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*option, QWidget*widget);
private:
    Palette plt;
};

#endif
