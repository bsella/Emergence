#include "headers/Function.h"

Function::InputNode::InputNode(uint rank):Node(Node::INPUT_G,1,10,Qt::white),_rank(rank){
	setFlag(ItemIsSelectable,false);
	setFlag(ItemIsMovable,false);
	setFlag(ItemIgnoresTransformations);
}
void Function::InputNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
	QRectF rect=boundingRect();
	painter->drawLine(rect.center()+QPointF(rect.width()/2,0),rect.center()+QPointF(rect.width()/2+socketSize,0));
}

Function::OutputNode::OutputNode():Node(Node::OUTPUT_G,1,1,Qt::white,1){
	setFlag(ItemIsSelectable,false);
	setFlag(ItemIsMovable,false);
	setFlag(ItemIgnoresTransformations);
}
void Function::OutputNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
	QRectF rect=boundingRect();
	painter->drawLine(rect.topLeft()+QPointF(0,height/2.0),rect.topLeft()+QPointF(socketSize,height/2.0));
}

FunctionNode* Function::currentFunction;
Function::Function(const QString &name, uint args):QListWidgetItem(name), nbArgs(args){
	scene= new QGraphicsScene;
	start= new OutputNode;
	scene->addItem(start);
	for(uint i=0;i<nbArgs;i++){
		iNodes.append(new InputNode(i));
		scene->addItem(iNodes[i]);
	}
}
Function::~Function(){
	for(int i=nbArgs-1;i>=0;i--){
		scene->removeItem(iNodes[i]);
		delete iNodes[i];
	}
	scene->removeItem(start);
	delete start;
	delete scene;
}
