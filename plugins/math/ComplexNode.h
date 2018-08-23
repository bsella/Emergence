#ifndef COMPLEXNODE_H
#define COMPLEXNODE_H

#include "Node.h"

class ComplexNode : public Node{
public:
	ComplexNode();
	inline static Node* makeNode(std::istream&){return new ComplexNode;}
private:
	data_t kernel()const;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
};

#endif // COMPLEXNODE_H
