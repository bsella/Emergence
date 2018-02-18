#include "include/MathGate.h"

MathGate::MathGate(unsigned i, unsigned n, unsigned w, unsigned h):Gate(i,w,h,QColor(180,255,180),n){}

ADDGate::ADDGate():MathGate(ADD_G,2){}
SUBGate::SUBGate():MathGate(SUB_G,2){}
MULGate::MULGate():MathGate(MUL_G,2){}
DIVGate::DIVGate():MathGate(DIV_G,2){}
NEGGate::NEGGate():MathGate(NEG_G,1){}
SQRTGate::SQRTGate():MathGate(SQRT_G,1){}
ABSGate::ABSGate():MathGate(ABS_G,1){}
LERPGate::LERPGate():MathGate(LERP_G,3,50,100){}
CLAMPGate::CLAMPGate():MathGate(CLAMP_G,3,50,100){}
SINGate::SINGate():MathGate(SIN_G,1){}
COSGate::COSGate():MathGate(COS_G,1){}
MINGate::MINGate():MathGate(MIN_G,2){}
MAXGate::MAXGate():MathGate(MAX_G,2){}

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
#include <iostream>
data_t ADDGate::eval(){
	if(validVal) {
		std::cout << val.d << std::endl;
		return val;
	}
	val= iGates[0]->eval()+iGates[1]->eval();
	validVal=true;
	return val;
}
data_t SUBGate::eval(){
	if(validVal) return val;
	val= iGates[0]->eval()-iGates[1]->eval();
	validVal=true;
	return val;
}
data_t MULGate::eval(){
	if(validVal) return val;
	val= iGates[0]->eval()*iGates[1]->eval();
	validVal=true;
	return val;
}
data_t DIVGate::eval(){
	if(validVal) return val;
	val= iGates[0]->eval()/iGates[1]->eval();
	validVal=true;
	return val;
}
data_t NEGGate::eval(){
	if(validVal) return val;
	val= -iGates[0]->eval();
	validVal=true;
	return val;
}
data_t SQRTGate::eval(){
	if(validVal) return val;
	val= qSqrt(iGates[0]->eval());
	validVal=true;
	return val;
}
data_t ABSGate::eval(){
	if(validVal) return val;
	val= qAbs((double)iGates[0]->eval());
	validVal=true;
	return val;
}
data_t LERPGate::eval(){
	if(validVal) return val;
	double alpha=iGates[1]->eval();
	val=(1.0-alpha)*double(iGates[2]->eval())+alpha*double(iGates[0]->eval());
	validVal=true;
	return val;
}
data_t CLAMPGate::eval(){
	if(validVal) return val;
	double min=iGates[2]->eval(), max=iGates[0]->eval();
	if(!(max-min)) return 0.0;
	val= (double(iGates[1]->eval())-min)/(max-min);
	validVal=true;
	return val;
}
data_t SINGate::eval(){
	if(validVal) return val;
	val= qSin(iGates[0]->eval());
	validVal=true;
	return val;
}
data_t COSGate::eval(){
	if(validVal) return val;
	val= qCos(iGates[0]->eval());
	validVal=true;
	return val;
}
data_t MINGate::eval(){
	if(validVal) return val;
	val= qMin(iGates[0]->eval(),iGates[1]->eval());
	validVal=true;
	return val;
}
data_t MAXGate::eval(){
	if(validVal) return val;
	val= qMax(iGates[0]->eval(),iGates[1]->eval());
	validVal=true;
	return val;
}
