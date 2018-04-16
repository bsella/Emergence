#include "include/RenderArea.h"

RenderArea::RenderArea(QWidget *parent):QWidget(parent){
	xg=new PixelXNode;
	yg=new PixelYNode;
	start=new RenderNode;
	ratio=new RatioNode;
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
	if(isValid()){
		emit valid(true);
		QPainter(this).drawImage(0,0,renderImage(width(),height()));
	}else emit valid(false);
}

bool RenderArea::isValid(){
	return *start;
}

void RenderArea::resizeEvent(QResizeEvent*){
	ratio->update(QWidget::width(),QWidget::height());
}

RenderArea::~RenderArea(){
	delete xg;
	delete yg;
	delete start;
	delete ratio;
}
