#include "include/nodes/RenderNode.h"

RenderNode::RenderArea::RenderArea(RenderNode *node, QWidget *parent):QDockWidget(parent){
	start=node;
	setFeatures(0);
	setWindowTitle("Output "+QString::number(start->outputNumber));
}

QImage RenderNode::RenderArea::renderImage(int w, int h){
	QImage image(w,h ,QImage::Format_ARGB32_Premultiplied);
	for(int i=0;i<w;i++)
		for(int j=0;j<h;j++){
			RenderNode::x=(double)i/w;
			RenderNode::y=(double)j/h;
			emit sm.updateXY();
			image.setPixel(i,j,start->eval());
		}
	return image;
}

void RenderNode::RenderArea::paintEvent(QPaintEvent *){
	if(*start)
		QPainter(this).drawImage(0,0,renderImage(width(),height()));
}

uint RenderNode::outputs=0;

void RenderNode::RenderArea::closeEvent(QCloseEvent*){
	start->inside=true;
	start->update();
}
void RenderNode::RenderArea::resizeEvent(QResizeEvent *){
	emit sm.updateXY();
}

RenderNode::RenderNode():Node(RENDER_G,50, 50, Qt::white,1,true){
	outputNumber=outputs++;
	output= new RenderArea(this);
}

data_t RenderNode::kernel()const{
	return iNodes[0]->eval();
}

void RenderNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
	if(inside){
		painter->drawLine(QPointF(0,height/2.0),QPointF(socketSize,height/2.0));
		painter->drawRect(QRectF(socketSize,0,width,height));
		if(*this)
			painter->drawImage(socketSize,0,output->renderImage(width+1,height+1));
	}else{
		pen.setColor(Qt::darkGreen);
		Node::paint(painter, option, widget);
		painter->setFont(QFont("",8));
		painter->drawText(boundingRect().center()-QPoint(18,-2),"Output "+QString::number(outputNumber));
	}
}

void RenderNode::updateTopology(){
	update();
	output->update();
}

void RenderNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *){
	inside=!inside;
	output->show();
	update();
}
