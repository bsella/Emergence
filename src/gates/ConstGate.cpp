#include "include/ConstGate.h"

ConstGate::ConstGate(double v):Gate(DOUBLE_G,50,50,QColor(255,255,180)){
	val=v;
}
ConstGate::ConstGate(uint v):Gate(COLOR_G,50,50,QColor(v)){
	val=v;
}

void ConstGate::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*widget){
	Gate::paint(painter,option,widget);
	switch(val.t){
	case TypeEnum::DOUBLE:
		painter->drawText(boundingRect().center()-QPoint(12,-2),QString::number(val.d));
		break;
	case TypeEnum::COLOR:
		painter->drawText(boundingRect().center()-QPoint(16,-2),"Color");
		break;
	default:
		break;
	}
}

void ConstGate::contextMenuEvent(QGraphicsSceneContextMenuEvent* event){
	menu=new QMenu;
	switch(val.t){
	case TypeEnum::DOUBLE:
		connect(menu->addAction(QString("Change number")), &QAction::triggered,this,&ConstGate::changeNumber);
		break;
	case TypeEnum::COLOR:
		connect(menu->addAction(QString("Change color")), &QAction::triggered,this,&ConstGate::changeColor);
		break;
	default:
		break;
	}
	Gate::contextMenuEvent(event);
}

data_t ConstGate::eval(){
	if(!validVal) validVal=true;
	return val;
}

void ConstGate::mouseDoubleClickEvent(QGraphicsSceneMouseEvent*){
	switch(val.t){
	case TypeEnum::DOUBLE:
		changeNumber();
		break;
	case TypeEnum::COLOR:
		changeColor();
		break;
	default:
		break;
	}
}

void ConstGate::changeColor(){
	QColor c =QColorDialog::getColor(Qt::white,(QWidget*)parentWidget());
	if(c.isValid()){
		val.u=c.rgba();
		color=c;
		updateOutputVal();
		update();
		emit notifyRA();
	}
}

void ConstGate::changeNumber(){
	bool ok;
	double d =QInputDialog::getDouble((QWidget*)parentWidget(),"Choose Number","",0,-2147483647,2147483647,3,&ok);
	if(ok){
		val.d=d;
		updateOutputVal();
		update();
		emit notifyRA();
	}
}
