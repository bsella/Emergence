#ifndef FUNCTIONNODE_H
#define FUNCTIONNODE_H

#include "Node.h"
#include "Function.h"

class FunctionNode: public Node{
public:
	FunctionNode(uint args=0);
	data_t eval();
private:
	Function* func;
	static FunctionNode* current;
	inline data_t kernel()const{return func->start->eval();}
	void changeNbArgs(uint args);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
	operator bool()const;
};

#endif // FUNCTIONNODE_H
