#include "nodes/FunctionNode.h"

#include "FunctionManager.h"

uint FunctionNode::nbNodes=0;

FunctionNode::FunctionNode(Function* f)
	:Node(FUNC_G,60,50+10*f->nbArgs,Qt::lightGray,f->nbArgs),
	func(f),nodeNumber(nbNodes++){}
FunctionNode::FunctionNode():Node(FUNC_G,60,50,Qt::lightGray),nodeNumber(nbNodes++){}
FunctionNode::~FunctionNode(){
	nbNodes--;
}

void FunctionNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *){
	Function* newFunc=FunctionManager::getFunction();
	if(newFunc){
		func=newFunc;
		changeNbArgs(func->nbArgs);
	}
	update();
}

void FunctionNode::paint(QPainter *p, const QStyleOptionGraphicsItem *o, QWidget *w){
	Node::paint(p,o,w);
	QRectF rect = boundingRect();
	if(func)
		p->drawText(rect.topLeft()+QPointF(8,rect.height()/2.0+4),func->text());
}

void FunctionNode::changeNbArgs(uint args){
	if(nbArgs==args) return;
	height=50+10*args;
	if(args>nbArgs)
		for(uint i=nbArgs; i<args; i++){
			sockets.push_back(new Socket(i,height*((i+1.0)/(args+1.0)),this));
			iNodes.push_back(nullptr);
		}
	else
		for(uint i=args; i<nbArgs; i++){
			sockets.back()->disconnectNode();
			delete sockets.back();
			sockets.pop_back();
			iNodes.pop_back();
		}
	nbArgs=args;
	update();
}

FunctionNode::operator bool()const{
	if(func)
		return Node::operator bool()&& *func->start;
	return false;
}

FunctionNode* FunctionNode::current;

data_t FunctionNode::eval(){
	if(constant) return cache;
	if(pixelID==lastPixelID) return cache;
	lastPixelID=pixelID;
	current=this;
	cache=kernel();
	current=nullptr;
	return cache;
}
