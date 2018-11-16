#include "ColorNode.h"

#include <QPainter>
#include <QColorDialog>

ColorNode::ColorNode(const data_t::color& c):Node("color",50,50,c){
	cache=c;
	constant=true;
}

void ColorNode::paint(QPainter *painter, const QStyleOptionGraphicsItem*option, QWidget*widget){
	Node::paint(painter,option,widget);
	painter->drawText(boundingRect().center()-QPoint(16,-2),"Color");
}
void ColorNode::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
	menu=new QMenu;
	connect(menu->addAction(QString("Change color")), &QAction::triggered,this,&ColorNode::changeColor);
	Node::contextMenuEvent(event);
}
void ColorNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *){
	changeColor();
}

void ColorNode::changeColor(){
	QColor c =QColorDialog::getColor(Qt::white,(QWidget*)parentWidget());
	if(c.isValid()){
		cache=c.rgba();
		color=c;
		updateVal();
		emit sm.updateOutputs();
		update();
	}
}

RGBNode::RGBNode():Node("rgb",50,100,Qt::white,3){}
HSVNode::HSVNode():Node("hsv",50,100,Qt::white,3){}

void RGBNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter, option, widget);
	painter->fillRect(QRect(socketSize+2,height/4-5,width-4,10),Qt::red);
	painter->fillRect(QRect(socketSize+2,2*height/4-5,width-4,10),Qt::green);
	painter->fillRect(QRect(socketSize+2,3*height/4-5,width-4,10),Qt::blue);
}

void HSVNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter, option, widget);
	painter->drawText(width/4,height/4+4,"H");
	painter->drawText(width/4,2*height/4+4,"S");
	painter->drawText(width/4,3*height/4+4,"V");
}

data_t RGBNode::kernel()const{
	int r=double(iNodes[0]->eval())*255,
		g=double(iNodes[1]->eval())*255,
		b=double(iNodes[2]->eval())*255;
	r=qMax(r,0); r= qMin(r,255);
	g=qMax(g,0); g= qMin(g,255);
	b=qMax(b,0); b= qMin(b,255);
	return qRgb(r,g,b);
}

data_t HSVNode::kernel()const{
	int h=double(iNodes[0]->eval())*360,
		s=double(iNodes[1]->eval())*255,
		v=double(iNodes[2]->eval())*255;
	h=qMax(h,0); h= qMin(h,359);
	s=qMax(s,0); s= qMin(s,255);
	v=qMax(v,0); v= qMin(v,255);
	return QColor::fromHsv(h,s,v).rgb();
}
