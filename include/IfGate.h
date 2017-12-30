#ifndef IFGATE_H
#define IFGATE_H

#include "Gate.h"
#include "FuncGate.h"

class IfGate:public FuncGate{
public:
	IfGate();
	data_t eval()const;
private:
	virtual void paint(QPainter* painter,
					   const QStyleOptionGraphicsItem* option,
					   QWidget*widget);
};

#endif
