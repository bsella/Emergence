#include "include/PaletteGate.h"

LUTGate::LUTGate(const Palette& p): Gate(PALETTE_G,140,70,Qt::white,1), plt(p){}

data_t LUTGate::eval(){
	if(validVal) return val;
	val= plt[iGates[0]->eval()];
	validVal=true;
	return val;
}

void LUTGate::paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
	Gate::paint(painter, option, widget);
	for(uint i=socketSize*2; i<width; i++){
		painter->setPen(plt[i/(double)width]);
		painter->drawLine(QPoint(i,10),QPoint(i,height-10));
	}
}
