#include "lib/PaletteGate.h"

PaletteGate::PaletteGate(const Palette& p): FuncGate(140,70,QColor(180,255,180),1), plt(p){}

data_t PaletteGate::eval()const{
    return plt[iGates[0]->eval()];
}

void PaletteGate::paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    FuncGate::paint(painter, option, widget);
}
