#ifndef FUNCTIONNODE_H
#define FUNCTIONNODE_H

#include "Node.h"
#include "Function.h"

class FunctionNode: public Node{
public:
	FunctionNode(Function *f);
	FunctionNode();
	~FunctionNode();
	data_t eval();
	static Node* makeNode(std::istream &);
	static FunctionNode* current;
	Function* func;
	const uint nodeNumber;
private:
	static uint nbNodes;
	inline data_t kernel()const{return func->start->eval();}
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
	void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
	operator bool()const;
	void changeNbArgs(uint args);
	void toBin(std::ostream&)const override;
	void toText(std::ostream&)const override;
};

#endif // FUNCTIONNODE_H
