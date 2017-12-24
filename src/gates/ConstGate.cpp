#include "lib/ConstGate.h"

ConstGate::ConstGate(double v):FuncGate(50,50,QColor(255,255,180)),_v(v){}

ConstGate::ConstGate(bool v):FuncGate(50,50,QColor(255,255,180)),_v(v){}

ConstGate::ConstGate(uint v):FuncGate(50,50,QColor(255,255,180)),_v(v){}

void ConstGate::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*widget){
    FuncGate::paint(painter,option,widget);
}
