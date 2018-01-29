#include "include/BitmapGate.h"

BitmapGate::BitmapGate():Gate(BITMAP_G,70,70,Qt::lightGray,2){
	bmp=nullptr;
}
BitmapGate::BitmapGate(const QString& filename):Gate(BITMAP_G,70,70,Qt::lightGray,2){
	setBMP(filename);
}

void BitmapGate::setBMP(const QString &filename){
	bmp= new QPixmap(filename);
	bmpWidth=bmp->width();
	bmpHeight=bmp->height();
}

data_t BitmapGate::eval()const{
	if(!bmp)
		return 0xff000000;
	int g0 = double(iGates[0]->eval())*bmpWidth;
	int g1 = double(iGates[1]->eval())*bmpHeight;
	if(g0<0 || g0>=bmpWidth || g1<0 || g1>=bmpHeight)
		return 0xff000000;
	return bmp->toImage().pixel(g0,g1);
}

void BitmapGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter,option,widget);
	if(bmp)
		for(uint x=10; x<width-10;x++)
			for(uint y= 10; y<height-10; y++){
				painter->setPen(bmp->toImage().pixel(double(x)/width*bmpWidth,double(y)/height*bmpHeight));
				painter->drawPoint(x,y);
			}
	else
		painter->drawText(boundingRect().center()-QPointF(12,-2),"BMP");
}

void BitmapGate::contextMenuEvent(QGraphicsSceneContextMenuEvent* event){
	menu=new QMenu;
	connect(menu->addAction(QString("Choose image")), &QAction::triggered,this,&BitmapGate::changeBMP);
	menu->addSeparator();
	Gate::contextMenuEvent(event);
}

void BitmapGate::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *){
	changeBMP();
}

void BitmapGate::changeBMP(){
	QString f= QFileDialog::getOpenFileName(0,"Choose Image",".","Images (*.bmp)");
	if(f.isNull())return;
	setBMP(f);
	update();
	emit notifyRA();
}

