#include "lib/RenderArea.h"

RenderArea::RenderArea(QWidget *parent):QWidget(parent){
	xg=new PixelXGate;
	yg=new PixelYGate;
	start=new RenderGate;
}

void RenderArea::paintEvent(QPaintEvent*){
	if(!*start) return;
	QImage image(size(),QImage::Format_ARGB32_Premultiplied);
	for(int x=0;x<width();x++)
		for(int y=0;y<height();y++){
			xg->update((double)x/width());
			yg->update((double)y/height());
			image.setPixel(x,y,start->eval());
		}
	QPainter(this).drawImage(0,0,image);
}

RenderArea::~RenderArea(){
	delete xg;
	delete yg;
	delete start;
}
