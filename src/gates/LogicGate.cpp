#include "include/LogicGate.h"

LogicGate::LogicGate(unsigned i,unsigned n):Gate(i,50,50,QColor(255,180,180),n){}

ORGate::ORGate():LogicGate(OR_G,2){}
ANDGate::ANDGate():LogicGate(AND_G,2){}
XORGate::XORGate():LogicGate(XOR_G,2){}
NOTGate::NOTGate():LogicGate(NOT_G,1){}

void ORGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option, widget);
	painter->drawText(boundingRect().center()-QPoint(10,-2),"OR");
}
void ANDGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option, widget);
	painter->drawText(boundingRect().center()-QPoint(12,-2),"AND");
}
void XORGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option, widget);
	painter->drawText(boundingRect().center()-QPoint(12,-2),"XOR");
}
void NOTGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option, widget);
	painter->drawText(boundingRect().center()-QPoint(12,-2),"NOT");
}

data_t ORGate::eval(){
	if(validVal) return val;
	val= iGates[0]->eval() || iGates[1]->eval();
	validVal=true;
	return val;
}

data_t ANDGate::eval(){
	if(validVal) return val;
	val= iGates[0]->eval() && iGates[1]->eval();
	validVal=true;
	return val;
}

data_t XORGate::eval(){
	if(validVal) return val;
	val= iGates[0]->eval() ^ iGates[1]->eval();
	validVal=true;
	return val;
}

data_t NOTGate::eval(){
	if(validVal) return val;
	val= !iGates[0]->eval();
	validVal=true;
	return val;
}
