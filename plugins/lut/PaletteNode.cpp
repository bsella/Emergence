#include "PaletteNode.h"

LUTNode::LUTNode(const Palette& p): Node("lut",140,70,Qt::white,1), plt(p){}

data_t LUTNode::kernel()const{
	return plt[iNodes[0]->eval()];
}

void LUTNode::paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
	Node::paint(painter, option, widget);
	for(uint i=socketSize*2; i<width; i++){
		painter->setPen(plt[i/(double)width]);
		painter->drawLine(QPoint(i,10),QPoint(i,height-10));
	}
}

Node* LUTNode::makeNode(std::istream&){
	Palette p;
	p.add(0xffff0000,0);
	p.add(0xff0000ff,.5);
	p.add(0xff00ff00,1);
	return new LUTNode(p);
}
