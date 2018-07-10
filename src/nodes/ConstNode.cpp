#include "include/nodes/ConstNode.h"

ConstNode::ConstNode(double v):Node(DOUBLE_G,50,50,QColor(255,255,180)){
	cache=v;
	constant=true;
}
ConstNode::ConstNode(data_t::color v):Node(COLOR_G,50,50,QColor(v)){
	cache=v;
	constant=true;
}

void ConstNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*widget){
	Node::paint(painter,option,widget);
	switch(cache.t){
	case TypeEnum::DOUBLE:
		painter->drawText(boundingRect().center()-QPoint(12,-2),QString::number(cache.d));
		break;
	case TypeEnum::COLOR:
		painter->drawText(boundingRect().center()-QPoint(16,-2),"Color");
		break;
	default:
		break;
	}
}

void ConstNode::contextMenuEvent(QGraphicsSceneContextMenuEvent* event){
	menu=new QMenu;
	switch(cache.t){
	case TypeEnum::DOUBLE:
		connect(menu->addAction(QString("Change number")), &QAction::triggered,this,&ConstNode::changeNumber);
		break;
	case TypeEnum::COLOR:
		connect(menu->addAction(QString("Change color")), &QAction::triggered,this,&ConstNode::changeColor);
		break;
	default:
		break;
	}
	Node::contextMenuEvent(event);
}

void ConstNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent*){
	switch(cache.t){
	case TypeEnum::DOUBLE:
		changeNumber();
		break;
	case TypeEnum::COLOR:
		changeColor();
		break;
	default:
		break;
	}
}

void ConstNode::changeColor(){
	QColor c =QColorDialog::getColor(Qt::white,(QWidget*)parentWidget());
	if(c.isValid()){
		cache=c.rgba();
		color=c;
		updateVal();
		emit sm.updateOutputs();
		update();
	}
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
