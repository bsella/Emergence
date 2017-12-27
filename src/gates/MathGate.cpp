#include "lib/MathGate.h"

MathGate::MathGate(unsigned n):FuncGate(50,50,QColor(180,255,180),n){}

ADDGate::ADDGate():MathGate(2){}
SUBGate::SUBGate():MathGate(2){}
MULGate::MULGate():MathGate(2){}
DIVGate::DIVGate():MathGate(2){}
NEGGate::NEGGate():MathGate(1){}
SQRTGate::SQRTGate():MathGate(1){}

void ADDGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	FuncGate::paint(painter,option,widget);
	painter->drawText(boundingRect().center(),"+");
}

void SUBGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	FuncGate::paint(painter,option,widget);
	painter->drawText(boundingRect().center(),"-");
}

void MULGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	FuncGate::paint(painter,option,widget);
	painter->drawText(boundingRect().center(),"*");
}

void DIVGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	FuncGate::paint(painter,option,widget);
	painter->drawText(boundingRect().center(),"/");
}

void NEGGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	FuncGate::paint(painter,option,widget);
	painter->drawText(boundingRect().center(),"(-)");
}

void SQRTGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	FuncGate::paint(painter,option,widget);
	painter->drawText(boundingRect().center()-QPointF(12,0),"sqrt");
}

data_t ADDGate::eval()const{
	return iGates[0]->eval()+iGates[1]->eval();
}
data_t SUBGate::eval()const{
	return iGates[0]->eval()-iGates[1]->eval();
}
data_t MULGate::eval()const{
	return iGates[0]->eval()*iGates[1]->eval();
}
data_t DIVGate::eval()const{
	return iGates[0]->eval()/iGates[1]->eval();
}
data_t NEGGate::eval()const{
	return -iGates[0]->eval();
}
data_t SQRTGate::eval()const{
	return qSqrt(iGates[0]->eval());
}
