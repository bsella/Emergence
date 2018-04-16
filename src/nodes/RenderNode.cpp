#include "include/nodes/RenderNode.h"

RenderNode::RenderNode():Node(RENDER_G,50, 50, Qt::white,1,true){}
data_t RenderNode::eval(){
	if(validVal) return val;
	val=iNodes[0]->eval();
	validVal=true;
	return val;
}

void RenderNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
	pen.setColor(Qt::darkGreen);
	Node::paint(painter, option, widget);
	painter->drawText(boundingRect().center()-QPoint(22,-2),"Output");
}

void RenderNode::removeNode(){
	Node::removeNode();
	emit deleted();
}
