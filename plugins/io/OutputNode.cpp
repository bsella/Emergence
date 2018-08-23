#include "OutputNode.h"

OutputNode::RenderArea::RenderArea(OutputNode *node, QWidget *parent):QDockWidget(parent){
	start=node;
	setFeatures(0);
	setWindowTitle("Output "+QString::number(start->outputNumber));
}

QImage OutputNode::RenderArea::renderImage(int w, int h){
	QImage image(w,h ,QImage::Format_ARGB32_Premultiplied);
	RatioNode::ratio=double(w)/h;
	Node::widthByHeight=w*h;
	emit sm.updateRatio();
	for(int i=0;i<w;i++)
		for(int j=0;j<h;j++){
			Node::pixelID= i+(j*w)+1;
			InputNode::input_x=(double)i/w;
			InputNode::input_y=(double)j/h;
			image.setPixel(i,j,start->eval());
		}
	return image;
}

void OutputNode::RenderArea::paintEvent(QPaintEvent *){
	if(*start)
		QPainter(this).drawImage(0,0,renderImage(width(),height()));
}

uint OutputNode::outputs=0;

void OutputNode::RenderArea::closeEvent(QCloseEvent*){
	start->inside=true;
	start->update();
}
void OutputNode::RenderArea::resizeEvent(QResizeEvent *){
	RatioNode::ratio=double(width())/height();
	Node::widthByHeight=width()*height();
	emit sm.updateRatio();
}

OutputNode::OutputNode():Node("out",50, 50, Qt::white,1,true){
	outputNumber=outputs++;
	output= new RenderArea(this);
	connect(&sm,&SignalManager::updateOutputs,this,&OutputNode::updateOutput);
}

OutputNode::~OutputNode(){
	disconnect(&sm,&SignalManager::updateOutputs,this,&OutputNode::updateOutput);
	delete output;
	outputs--;
}

data_t OutputNode::kernel()const{
	return iNodes[0]->eval();
}

void OutputNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
	pen.setColor(isSelected()?Qt::darkGreen:Qt::black);
	if(inside){
		pen.setWidth(isSelected()?2:1);
		painter->setPen(pen);
		painter->drawLine(QPointF(0,height/2.0),QPointF(socketSize,height/2.0));
		painter->drawRect(QRectF(socketSize,0,width,height));
		if(*this)
			painter->drawImage(socketSize+1,1,output->renderImage(width-1,height-1));
	}else{
		Node::paint(painter, option, widget);
		painter->setFont(QFont("",8));
		painter->drawText(boundingRect().center()-QPoint(18,-2),"Output "+QString::number(outputNumber));
	}
}

void OutputNode::updateOutput(){
	update();
	output->update();
}

void OutputNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *){
	if(inside)
		output->show();
	else
		output->close();
	inside=!inside;
	update();
}
