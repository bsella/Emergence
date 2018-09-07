#include "LUTNode.h"

#include "dialog/lut_dialog.h"
#include <QPainter>

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
	Palette *p= LutDialog::getPalette();
	if(p)return  new LUTNode(*p);
	return nullptr;
}
