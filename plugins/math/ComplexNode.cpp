#include "nodes/ComplexNode.h"

ComplexNode::ComplexNode():Node(CPLX_G,50,50,Qt::white,2){
}

void ComplexNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	drawIcon(painter,":/icons/complex.png");
}

data_t ComplexNode::kernel()const{
	return cplx(iNodes[0]->eval(),iNodes[1]->eval());
}
