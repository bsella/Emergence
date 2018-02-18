#ifndef RENDERGATE_H
#define RENDERGATE_H

#include "Gate.h"

class RenderGate : public Gate{
public:
	RenderGate();
	data_t eval();
private:
	void removeGate();
	void paint(QPainter* painter,
			   const QStyleOptionGraphicsItem* option,
			   QWidget* widget);
};

#endif // RENDERGATE_H
