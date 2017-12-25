#ifndef CONSTGATE_H
#define CONSTGATE_H

#include "FuncGate.h"

class ConstGate:public FuncGate{
public:
	ConstGate(double v);
	ConstGate(bool v);
	ConstGate(uint v);
	inline data_t eval()const{return _v;}
private:
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*widget);
	data_t _v;
};

#endif
