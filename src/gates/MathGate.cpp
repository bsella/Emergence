#include "include/MathGate.h"

MathGate::MathGate(unsigned n, unsigned w, unsigned h):FuncGate(w,h,QColor(180,255,180),n){}

ADDGate::ADDGate():MathGate(2){}
SUBGate::SUBGate():MathGate(2){}
MULGate::MULGate():MathGate(2){}
DIVGate::DIVGate():MathGate(2){}
NEGGate::NEGGate():MathGate(1){}
SQRTGate::SQRTGate():MathGate(1){}
ABSGate::ABSGate():MathGate(1){}
LERPGate::LERPGate():MathGate(3,50,100){}
CLAMPGate::CLAMPGate():MathGate(3,50,100){}

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
void ABSGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	FuncGate::paint(painter,option,widget);
	painter->drawText(boundingRect().center()-QPointF(12,0),"abs");
}
void LERPGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	FuncGate::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.topLeft()+QPointF(8,rect.height()/4.0+4),"1");
	painter->drawText(rect.topLeft()+QPointF(width/2,2*rect.height()/4.0+4),"lerp");
	painter->drawText(rect.topLeft()+QPointF(8,3*rect.height()/4.0+4),"0");
}
void CLAMPGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	FuncGate::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.topLeft()+QPointF(8,rect.height()/4.0+4),"1");
	painter->drawText(rect.topLeft()+QPointF(width/2-10,2*rect.height()/4.0+4),"clamp");
	painter->drawText(rect.topLeft()+QPointF(8,3*rect.height()/4.0+4),"0");
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
data_t ABSGate::eval()const{
	return qAbs((double)iGates[0]->eval());
}
data_t LERPGate::eval()const{
	double alpha=iGates[1]->eval();
	return (1.0-alpha)*double(iGates[2]->eval())+alpha*double(iGates[0]->eval());
}
data_t CLAMPGate::eval()const{
	double min=iGates[2]->eval(), max=iGates[0]->eval();
	if(!(max-min)) return 0.0;
	return (double(iGates[1]->eval())-min)/(max-min);
}
