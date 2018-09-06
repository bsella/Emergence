#ifndef LUTNODE_H
#define LUTNODE_H

#include "Palette.h"
#include "Node.h"

class LUTNode:public Node{
public:
	LUTNode(const Palette& p);
	static Node* makeNode(std::istream &);
private:
	void paint(QPainter* painter, const QStyleOptionGraphicsItem*option, QWidget*widget);
	data_t kernel()const;
	Palette plt;
};

#endif
