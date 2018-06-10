#include "include/RenderArea.h"

RenderArea::RenderArea(QWidget *parent):QWidget(parent){
	xg=new PixelXNode;
	yg=new PixelYNode;
	start= new RenderNode;
	ratio=new RatioNode;
	connect(start,SIGNAL(notifyRA()),this,SLOT(update()));
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
	if(*start)
		QPainter(this).drawImage(0,0,renderImage(width(),height()));
}

void RenderArea::resizeEvent(QResizeEvent*){
	ratio->update(QWidget::width(),QWidget::height());
}
