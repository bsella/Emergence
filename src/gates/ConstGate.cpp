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
