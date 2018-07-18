#include "headers/FunctionWorkspace.h"
#include "commands.h"

FunctionWorkspace::FunctionWorkspace(QWidget *parent)
	:Workspace(parent){}
FunctionWorkspace::~FunctionWorkspace(){}

void FunctionWorkspace::dragEnterEvent(QDragEnterEvent *event){
	Workspace::dragEnterEvent(event);
	event->setAccepted(event->isAccepted()&& event->mimeData()->data("type").toInt()!=Node::FUNC_G);
}

void FunctionWorkspace::_setFunction(QListWidgetItem *fun){
	setFunction((Function*)fun);
	updateFunctionNodes();
}
void FunctionWorkspace::setFunction(Function *fun){
	func=fun;
	setScene(func->scene);
}

void FunctionWorkspace::resizeEvent(QResizeEvent *){
	updateFunctionNodes();
}
void FunctionWorkspace::wheelEvent(QWheelEvent *event){
	Workspace::wheelEvent(event);
	updateFunctionNodes();
}
void FunctionWorkspace::updateFunctionNodes() const{
	func->start->setPos(mapToScene(rect().right()-Node::Socket::headSize,rect().height()/2));
	for(auto& n: func->iNodes){
		uint y= double(n->_rank+1)/(func->nbArgs+1)*rect().height();
		n->setPos(mapToScene(-n->width-2*Node::socketSize,y));
	}
}
