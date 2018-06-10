#include "include/nodes/RenderNode.h"

RenderNode::RenderNode():Node(RENDER_G,50, 50, Qt::white,1,true){}

data_t RenderNode::kernel()const{
	return iNodes[0]->eval();
}

void RenderNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
	pen.setColor(Qt::darkGreen);
	Node::paint(painter, option, widget);
	painter->drawText(boundingRect().center()-QPoint(18,-2),"Output");
}

void RenderNode::updateTopology(){
	emit notifyRA();
}
