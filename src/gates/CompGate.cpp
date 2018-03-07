#include "include/gates/CompGate.h"

CompGate::CompGate(unsigned i):Gate(i,50,50,QColor(255,180,180),2){}

GTGate::GTGate():CompGate(GT_G){}
LTGate::LTGate():CompGate(LT_G){}
EQGate::EQGate():CompGate(EQ_G){}
NEGate::NEGate():CompGate(NE_G){}

void GTGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	drawIcon(painter,":/icons/greater_than.png");
}
void NEGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	drawIcon(painter,":/icons/not_equal.png");
}
void EQGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	drawIcon(painter,":/icons/equal.png");
}
void LTGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	drawIcon(painter,":/icons/less_than.png");
}
data_t GTGate::eval(){
	if(validVal) return val;
	val= iGates[0]->eval() > iGates[1]->eval();
	validVal=true;
	return val;
}

data_t LTGate::eval(){
	if(validVal) return val;
	val= iGates[0]->eval() < iGates[1]->eval();
	validVal=true;
	return val;
}

data_t EQGate::eval(){
	if(validVal) return val;
	val= iGates[0]->eval() == iGates[1]->eval();
	validVal=true;
	return val;
}

data_t NEGate::eval(){
	if(validVal) return val;
	val= iGates[0]->eval() != iGates[1]->eval();
	validVal=true;
	return val;
}
