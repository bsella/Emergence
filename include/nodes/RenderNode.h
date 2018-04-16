#ifndef RENDERNODE_H
#define RENDERNODE_H

#include "Node.h"

class RenderNode : public Node{
public:
	RenderNode();
	data_t eval();
private:
	void removeNode();
	void paint(QPainter* painter,
			   const QStyleOptionGraphicsItem* option,
			   QWidget* widget);
};

#endif // RENDERNODE_H
