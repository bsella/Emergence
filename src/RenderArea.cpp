#include "include/RenderArea.h"

RenderArea::RenderArea(QWidget *parent):QWidget(parent){
	xg=new PixelXGate;
	yg=new PixelYGate;
	start=new RenderGate;
}

QImage RenderArea::renderImage(int w, int h){
	QImage image(w,h ,QImage::Format_ARGB32_Premultiplied);
	for(int x=0;x<w;x++)
		for(int y=0;y<h;y++){
			xg->update((double)x/w);
			yg->update((double)y/h);
			image.setPixel(x,y,start->eval());
		}
	return image;
}

void RenderArea::paintEvent(QPaintEvent*){
	if(!isValid()){
		emit notValid();
		return;
	}
	emit valid();
	QPainter(this).drawImage(0,0,renderImage(width(),height()));
}

bool RenderArea::isValid(){
	return *start;
}

RenderArea::~RenderArea(){
	delete xg;
	delete yg;
	delete start;
}
