#ifndef IFGATE_H
#define IFGATE_H

#include "Gate.h"

class IfGate:public Gate{
public:
	IfGate();
	data_t eval()const;
private:
	virtual void paint(QPainter* painter,
					   const QStyleOptionGraphicsItem* option,
					   QWidget*widget);
};

#endif
