#include "headers/FunctionWorkspace.h"

FunctionWorkspace::FunctionWorkspace(QWidget *parent)
	:Workspace(parent){
//	outputSocket= new Socket;
}
FunctionWorkspace::~FunctionWorkspace(){
}

FunctionWorkspace::Socket::Socket():Node::Socket(0,0,0){
}
FunctionWorkspace::Socket::~Socket(){}
void FunctionWorkspace::Socket::connectToNode(Node *n){
	parent->func->start=n;
}
void FunctionWorkspace::Socket::disconnectNode(){
	parent->func->start=nullptr;
}

void FunctionWorkspace::dragEnterEvent(QDragEnterEvent *event){
	Workspace::dragEnterEvent(event);
	event->setAccepted(event->isAccepted()&& event->mimeData()->data("type").toInt()!=Node::FUNC_G);
}

void FunctionWorkspace::setFunction(Function *fun){
	func=fun;
	setScene(fun->scene);
}
