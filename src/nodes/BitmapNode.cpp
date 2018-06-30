#include "include/nodes/BitmapNode.h"

BitmapNode::BitmapNode(const QString& filename):Node(BITMAP_G,70,70,Qt::lightGray,2){
	setBMP(filename);
}

BitmapNode::~BitmapNode(){
	delete bmp;
}

void BitmapNode::setBMP(const QString &filename){
	bmp= new QPixmap(filename);
	bmpWidth=bmp->width();
	bmpHeight=bmp->height();
}

data_t BitmapNode::kernel()const{
	if(!bmp) return 0xff000000;
	int g0 = double(iNodes[0]->eval())*bmpWidth;
	int g1 = double(iNodes[1]->eval())*bmpHeight;
	if(g0<0 || g0>=bmpWidth || g1<0 || g1>=bmpHeight)
		return 0xff000000;
	return bmp->toImage().pixel(g0,g1);
}

QImage BitmapNode::scaleImage(uint w, uint h) const{
	QImage image(w,h,QImage::Format_ARGB32_Premultiplied);
	for(uint i=0; i<w; i++)
		for(uint j=0; j<h; j++)
			image.setPixel(i,j,bmp->toImage().pixel(double(i)/w*bmpWidth,double(j)/h*bmpHeight));
	return image;
}

void BitmapNode::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
	pen.setWidth(isSelected()?2:1);
	painter->setPen(pen);
	painter->drawLine(QPointF(0,height/(3.0)),QPointF(socketSize,height/(3.0)));
	painter->drawLine(QPointF(0,2*height/(3.0)),QPointF(socketSize,2*height/(3.0)));
	painter->drawRect(socketSize,0,width,height);
	QRectF rect= boundingRect();
	painter->drawLine(rect.center()+QPointF(rect.width()/2,0),rect.center()+QPointF(rect.width()/2-socketSize,0));
	if(bmp)
		painter->drawImage(socketSize+1,1,scaleImage(width-1,height-1));
	else
		painter->drawText(boundingRect().center()-QPointF(12,-2),"BMP");
}

void BitmapNode::contextMenuEvent(QGraphicsSceneContextMenuEvent* event){
	menu=new QMenu;
	connect(menu->addAction(QString("Choose image")), &QAction::triggered,this,&BitmapNode::changeBMP);
	menu->addSeparator();
	Node::contextMenuEvent(event);
}

void BitmapNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *){
	changeBMP();
}

void BitmapNode::changeBMP(){
	QString f= QFileDialog::getOpenFileName(0,"Choose Image",".","Images (*.bmp)");
	if(f.isNull())return;
	setBMP(f);
	updateVal();
	updateTopology();
	update();
}
