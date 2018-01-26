#include "include/MathGate.h"

MathGate::MathGate(unsigned n, unsigned w, unsigned h):Gate(w,h,QColor(180,255,180),n){}

ADDGate::ADDGate():MathGate(2){}
SUBGate::SUBGate():MathGate(2){}
MULGate::MULGate():MathGate(2){}
DIVGate::DIVGate():MathGate(2){}
NEGGate::NEGGate():MathGate(1){}
SQRTGate::SQRTGate():MathGate(1){}
ABSGate::ABSGate():MathGate(1){}
LERPGate::LERPGate():MathGate(3,50,100){}
CLAMPGate::CLAMPGate():MathGate(3,50,100){}
SINGate::SINGate():MathGate(1){}
COSGate::COSGate():MathGate(1){}
MINGate::MINGate():MathGate(2){}
MAXGate::MAXGate():MathGate(2){}

void ADDGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	drawIcon(painter,":/icons/add.png");
}

void SUBGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	drawIcon(painter,":/icons/subtract.png");
}

void MULGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	drawIcon(painter,":/icons/multiply.png");
}

void DIVGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	drawIcon(painter,":/icons/divide.png");
}

void NEGGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	drawIcon(painter,":/icons/subtract.png");
}

void SQRTGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	QImage icon=QImage(":/icons/sqrt.png");
	painter->drawImage(width/2-icon.width()/2+5,height/2-icon.height()/2,icon);
}
void ABSGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	painter->drawText(boundingRect().center()-QPointF(12,0),"abs");
}
void LERPGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.topLeft()+QPointF(8,rect.height()/4.0+4),"1");
	painter->drawText(rect.topLeft()+QPointF(width/2,2*rect.height()/4.0+4),"lerp");
	painter->drawText(rect.topLeft()+QPointF(8,3*rect.height()/4.0+4),"0");
}
void CLAMPGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.topLeft()+QPointF(8,rect.height()/4.0+4),"1");
	painter->drawText(rect.topLeft()+QPointF(width/2-10,2*rect.height()/4.0+4),"clamp");
	painter->drawText(rect.topLeft()+QPointF(8,3*rect.height()/4.0+4),"0");
}
void SINGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	painter->drawText(boundingRect().center()-QPointF(12,0),"sin");
}
void COSGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	painter->drawText(boundingRect().center()-QPointF(12,0),"cos");
}
void MINGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	painter->drawText(boundingRect().center()-QPointF(12,0),"min");
}
void MAXGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	painter->drawText(boundingRect().center()-QPointF(12,0),"max");
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
data_t SINGate::eval()const{
	return qSin(iGates[0]->eval());
}
data_t COSGate::eval()const{
	return qCos(iGates[0]->eval());
}
data_t MINGate::eval()const{
	return qMin(iGates[0]->eval(),iGates[1]->eval());
}
data_t MAXGate::eval()const{
	return qMax(iGates[0]->eval(),iGates[1]->eval());
}
