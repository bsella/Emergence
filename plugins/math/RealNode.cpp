#include "RealNode.h"

RealNode::RealNode(double v):Node("real",50,50,QColor(255,255,180)){
	cache=v;
	constant=true;
}

void ConstNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*widget){
	Node::paint(painter,option,widget);
	painter->drawText(boundingRect().center()-QPoint(12,-2),QString::number(cache.d));
}

void ConstNode::contextMenuEvent(QGraphicsSceneContextMenuEvent* event){
	menu=new QMenu;
	connect(menu->addAction(QString("Change number")), &QAction::triggered,this,&RealNode::changeNumber);
	Node::contextMenuEvent(event);
}

void ConstNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent*){
	changeNumber();
}

void ConstNode::changeNumber(){
	bool ok;
	double d =QInputDialog::getDouble((QWidget*)parentWidget(),"Choose Number","",0,-2147483647,2147483647,3,&ok);
	if(ok){
		cache=d;
		updateVal();
		emit sm.updateOutputs();
		update();
	}
}
