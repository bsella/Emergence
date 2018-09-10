#include "LUTNode.h"

#include "dialog/lut_dialog.h"
#include <QPainter>

LUTNode::LUTNode(const Gradient &g): Node("lut",140,70,Qt::white,1), gradient(g){}

data_t LUTNode::kernel()const{
	return gradient[iNodes[0]->eval()];
}

void LUTNode::paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
	Node::paint(painter, option, widget);
	for(uint i=socketSize*2; i<width; i++){
		painter->setPen(gradient[i/(double)width]);
		painter->drawLine(QPoint(i,10),QPoint(i,height-10));
	}
}

Node* LUTNode::makeNode(std::istream&){
	Gradient *g= LutDialog::getGradient();
	if(g)return new LUTNode(*g);
	return nullptr;
}
