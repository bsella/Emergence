#include "lib/ConstGate.h"

ConstGate::ConstGate(double v):FuncGate(50,50,QColor(255,255,180)),_v(v){
    t=TypeEnum::DOUBLE;
}

ConstGate::ConstGate(bool v):FuncGate(50,50,QColor(255,255,180)),_v(v){
    t=TypeEnum::BOOL;
}

ConstGate::ConstGate(uint v):FuncGate(50,50,QColor(v)),_v(v){
    t=TypeEnum::UINT;
}

void ConstGate::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*widget){
    FuncGate::paint(painter,option,widget);
    switch (t) {
    case TypeEnum::BOOL:
        painter->drawText(boundingRect().center()-QPoint(12,-2),_v.b?"True":"False");
        break;
    case TypeEnum::DOUBLE:
        painter->drawText(boundingRect().center()-QPoint(12,-2),QString::number(_v.d));
        break;
    case TypeEnum::UINT:
        painter->drawText(boundingRect().center()-QPoint(16,-2),"Color");
        break;
    default:
        break;
    }
}

void ConstGate::contextMenuEvent(QGraphicsSceneContextMenuEvent* event){
	menu=new QMenu;
	switch (t) {
	case TypeEnum::BOOL:
		break;
	case TypeEnum::DOUBLE:
		connect(menu->addAction(QString("Change number")), &QAction::triggered,this,&ConstGate::changeNumber);
		break;
	case TypeEnum::UINT:
		connect(menu->addAction(QString("Change color")), &QAction::triggered,this,&ConstGate::changeColor);
		break;
	default:
		break;
	}
	FuncGate::contextMenuEvent(event);
}

void ConstGate::changeColor(){
	QColor c =QColorDialog::getColor();
	if(c.isValid()){
		_v.u=c.rgba();
		color=c;
		update();
	}
}

void ConstGate::changeNumber(){
	bool ok;
	double d =QInputDialog::getDouble(0,"Choose Number","",0,-2147483647,2147483647,3,&ok);
	if(ok){
		_v.d=d;
		update();
	}
}
