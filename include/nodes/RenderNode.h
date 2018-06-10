#ifndef RENDERNODE_H
#define RENDERNODE_H

#include "Node.h"

class RenderNode : public Node{
public:
	RenderNode();
private:
	data_t kernel()const;
	void updateTopology();
	void paint(QPainter* painter,
			   const QStyleOptionGraphicsItem* option,
			   QWidget* widget);
signals:
	void updateRenderArea();
};

#endif // RENDERNODE_H
