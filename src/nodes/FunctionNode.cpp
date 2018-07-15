#include "nodes/FunctionNode.h"

FunctionNode::FunctionNode(uint args)
	:Node(FUNC_G,60,50+10*args,Qt::lightGray,args){

}
void FunctionNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}

void FunctionNode::changeNbArgs(uint args){
}

FunctionNode::operator bool()const{
	return func->start;
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
