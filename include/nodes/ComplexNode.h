#ifndef COMPLEXNODE_H
#define COMPLEXNODE_H

#include "Node.h"

class ComplexNode : public Node{
public:
	ComplexNode();
private:
	data_t eval();
	void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
};

#endif // COMPLEXNODE_H
