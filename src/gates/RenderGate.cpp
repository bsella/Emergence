#include "include/gates/RenderGate.h"

RenderGate::RenderGate():Gate(RENDER_G,50, 50, Qt::white,1,true){}
data_t RenderGate::eval(){
	if(validVal) return val;
	val=iGates[0]->eval();
	validVal=true;
	return val;
}

void RenderGate::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
	pen.setColor(Qt::darkGreen);
	Gate::paint(painter, option, widget);
	painter->drawText(boundingRect().center()-QPoint(22,-2),"Output");
}

void RenderGate::removeGate(){
	Gate::removeGate();
	emit deleted();
}
