#ifndef PALETTENODE_H
#define PALETTENODE_H

#include <include/Palette.h>
#include "Node.h"

class LUTNode:public Node{
public:
	LUTNode(const Palette& p);
private:
	void paint(QPainter* painter, const QStyleOptionGraphicsItem*option, QWidget*widget);
	data_t kernel()const;
	Palette plt;
};

#endif
