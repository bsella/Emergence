#include "include/CompGate.h"

CompGate::CompGate():Gate(50,50,QColor(255,180,180),2){}

void GTGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.x()+rect.width()/2-3,rect.y()+rect.height()/2+3,">");
}
void NEGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.x()+rect.width()/2-3,rect.y()+rect.height()/2+3,"!=");
}
void EQGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.x()+rect.width()/2-3,rect.y()+rect.height()/2+3,"=");
}
void LTGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.x()+rect.width()/2-3,rect.y()+rect.height()/2+3,"<");
}
data_t GTGate::eval()const{
	return iGates[0]->eval() > iGates[1]->eval();
}

data_t LTGate::eval()const{
	return iGates[0]->eval() < iGates[1]->eval();
}

data_t EQGate::eval()const{
	return iGates[0]->eval() == iGates[1]->eval();
}

data_t NEGate::eval()const{
	return iGates[0]->eval() != iGates[1]->eval();
}
