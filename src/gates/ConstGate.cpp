#include "include/ConstGate.h"

ConstGate::ConstGate(double v):Gate(DOUBLE_G,50,50,QColor(255,255,180)),_v(v){}
ConstGate::ConstGate(uint v):Gate(COLOR_G,50,50,QColor(v)),_v(v){}

void ConstGate::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*widget){
	Gate::paint(painter,option,widget);
	switch(_v.t){
	case TypeEnum::DOUBLE:
        painter->drawText(boundingRect().center()-QPoint(12,-2),QString::number(_v.d));
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
	switch(_v.t){
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

void ConstGate::mouseDoubleClickEvent(QGraphicsSceneMouseEvent*){
	switch(_v.t){
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
		_v.u=c.rgba();
		color=c;
		update();
		emit notifyRA();
	}
}

void ConstGate::changeNumber(){
	bool ok;
	double d =QInputDialog::getDouble((QWidget*)parentWidget(),"Choose Number","",0,-2147483647,2147483647,3,&ok);
	if(ok){
		_v.d=d;
		update();
		emit notifyRA();
	}
}
