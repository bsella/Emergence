#ifndef IFNODE_H
#define IFNODE_H

#include "Node.h"

class IfNode:public Node{
public:
	IfNode();
private:
	data_t eval();
	void paint(QPainter* painter,
				const QStyleOptionGraphicsItem* option,
				QWidget*widget);
};

#endif
