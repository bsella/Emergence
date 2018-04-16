#include "include/nodes/BitmapNode.h"

BitmapNode::BitmapNode():Node(BITMAP_G,70,70,Qt::lightGray,2){
	bmp=nullptr;
}
BitmapNode::BitmapNode(const QString& filename):Node(BITMAP_G,70,70,Qt::lightGray,2){
	setBMP(filename);
}

void BitmapNode::setBMP(const QString &filename){
	bmp= new QPixmap(filename);
	bmpWidth=bmp->width();
	bmpHeight=bmp->height();
	updateOutputVal();
}

data_t BitmapNode::eval(){
	if(validVal) return val;
	if(!bmp) return 0xff000000;
	int g0 = double(iNodes[0]->eval())*bmpWidth;
	int g1 = double(iNodes[1]->eval())*bmpHeight;
	if(g0<0 || g0>=bmpWidth || g1<0 || g1>=bmpHeight)
		return 0xff000000;
	val= bmp->toImage().pixel(g0,g1);
	validVal=true;
	return val;
}

void BitmapNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	if(bmp)
		for(uint x=10; x<width-10;x++)
			for(uint y= 10; y<height-10; y++){
				painter->setPen(bmp->toImage().pixel(double(x)/width*bmpWidth,double(y)/height*bmpHeight));
				painter->drawPoint(x,y);
			}
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
	update();
	emit notifyRA();
}

BitmapNode::~BitmapNode(){
	delete bmp;
}
