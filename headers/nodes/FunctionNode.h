#ifndef FUNCTIONNODE_H
#define FUNCTIONNODE_H

#include "Node.h"
#include "Function.h"

class FunctionNode: public Node{
public:
	FunctionNode(Function *f);
	FunctionNode();
	data_t eval();
	static FunctionNode* current;
	Function* func;
private:
	inline data_t kernel()const{return func->start->eval();}
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
	void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
	operator bool()const;
	void changeNbArgs(uint args);
};

#endif // FUNCTIONNODE_H
