#ifndef FUNCTIONNODE_H
#define FUNCTIONNODE_H

#include "Node.h"
#include "FunctionWorkspace.h"

class FunctionNode: public Node{
public:
	FunctionNode(uint args=0);
private:
	FunctionWorkspace* function;
	inline data_t kernel()const{return function->start->eval();}
	void changeNbArgs(uint args);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
	operator bool()const;
};

#endif // FUNCTIONNODE_H
