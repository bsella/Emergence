#ifndef RENDERGATE_H
#define RENDERGATE_H

#include "FuncGate.h"

class RenderGate : public FuncGate{
public:
	RenderGate();
	data_t eval()const;
private:
	void removeGate();
	void paint(QPainter* painter,
			   const QStyleOptionGraphicsItem* option,
			   QWidget* widget);
};

#endif // RENDERGATE_H
