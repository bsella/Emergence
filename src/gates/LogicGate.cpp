#include "include/LogicGate.h"

LogicGate::LogicGate(unsigned n):Gate(50,50,QColor(255,180,180),n){}

ORGate::ORGate():LogicGate(2){}
ANDGate::ANDGate():LogicGate(2){}
XORGate::XORGate():LogicGate(2){}
NOTGate::NOTGate():LogicGate(1){}

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

data_t ORGate::eval()const{
    return iGates[0]->eval() || iGates[1]->eval();
}

data_t ANDGate::eval()const{
    return iGates[0]->eval() && iGates[1]->eval();
}

data_t XORGate::eval()const{
    return iGates[0]->eval() ^ iGates[1]->eval();
}

data_t NOTGate::eval()const{
    return !iGates[0]->eval();
}
