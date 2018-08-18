#ifndef PALETTENODE_H
#define PALETTENODE_H

#include "Palette.h"
#include "Node.h"

class LUTNode:public Node{
public:
	LUTNode(const Palette& p);
	static Node* makeNode(void*);
private:
	void paint(QPainter* painter, const QStyleOptionGraphicsItem*option, QWidget*widget);
	data_t kernel()const;
	Palette plt;
};

#endif
