#include "include/gates/PixelGate.h"

void PixelGate::update(double i){
	val=i;
	updateOutputVal();
}
void RatioGate::update(unsigned x, unsigned y){
	val=double(x)/y;
	updateOutputVal();
}
void PixelGate::removeGate(){
	Gate::removeGate();
	emit deleted();
}
PixelGate::PixelGate(unsigned i):Gate(i,70,50,Qt::lightGray){
	validVal=true;
}
PixelXGate::PixelXGate():PixelGate(X_G){}
PixelYGate::PixelYGate():PixelGate(Y_G){}
RatioGate::RatioGate():PixelGate(RATIO_G){}

void PixelGate::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
	QRectF rect=boundingRect();
	rect.setRight(rect.right()-socketSize);
	painter->setRenderHint(QPainter::Antialiasing);
	QPainterPath path;
	path.addRoundedRect(rect, 10, 10);
	painter->setPen(pen);
	painter->fillPath(path, Qt::lightGray);
	painter->drawPath(path);
	painter->drawLine(rect.center()+QPointF(rect.width()/2,0),rect.center()+QPointF(rect.width()/2+socketSize,0));
}

void PixelXGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	PixelGate::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.center()+QPointF(-5,3),"X");
}
void PixelYGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	PixelGate::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.x()+rect.width()/2-5,rect.y()+rect.height()/2+3,"Y");
}

void RatioGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	PixelGate::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.x()+rect.width()/3,rect.y()+rect.height()/2+3,"X/Y");
}
