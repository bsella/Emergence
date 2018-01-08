#ifndef IFGATE_H
#define IFGATE_H

#include "Gate.h"

class IfGate:public Gate{
public:
	IfGate();
private:
	data_t eval()const;
	void paint(QPainter* painter,
					   const QStyleOptionGraphicsItem* option,
					   QWidget*widget);
};

#endif
