#ifndef IFNODE_H
#define IFNODE_H

#include "Node.h"

class IfNode:public Node{
public:
	IfNode();
private:
	data_t kernel()const;
	void paint(QPainter* painter,
				const QStyleOptionGraphicsItem* option,
				QWidget*widget);
};

#endif
