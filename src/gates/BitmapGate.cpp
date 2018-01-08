#include "include/BitmapGate.h"

BitmapGate::BitmapGate(QString filename):Gate(70,70,Qt::lightGray,2){
	bmp= new QPixmap(filename);
	bmpWidth=bmp->width();
	bmpHeight=bmp->height();
}

data_t BitmapGate::eval()const{
	int g0 = double(iGates[0]->eval())*bmpWidth;
	int g1 = double(iGates[1]->eval())*bmpHeight;
	if(g0<0 || g0>=bmpWidth || g1<0 || g1>=bmpHeight)
		return 0xff000000;
	return bmp->toImage().pixel(g0,g1);
}

void BitmapGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	for(uint x=10; x<width-10;x++)
		for(uint y= 10; y<height-10; y++){
			painter->setPen(bmp->toImage().pixel(double(x)/width*bmpWidth,double(y)/height*bmpHeight));
			painter->drawPoint(x,y);
		}
}
