#include "lib/PaletteGate.h"

PaletteGate::PaletteGate(const Palette& p): FuncGate(140,70,Qt::white,1), plt(p){}

data_t PaletteGate::eval()const{
    return plt[iGates[0]->eval()];
}

void PaletteGate::paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    FuncGate::paint(painter, option, widget);
    for(uint i=socketSize*2; i<width; i++){
        painter->setPen(plt[i/(double)width]);
        painter->drawLine(QPoint(i,10),QPoint(i,height-10));
    }

}
