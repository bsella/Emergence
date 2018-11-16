#ifndef LUTNODE_H
#define LUTNODE_H

#include "Gradient.h"
#include "Node.h"

class LUTNode:public Node{
public:
	LUTNode(const Gradient& p);
	static Node* makeNode(std::istream &);
private:
	void paint(QPainter* painter, const QStyleOptionGraphicsItem*option, QWidget*widget);
	data_t kernel()const;
	Gradient gradient;
	void toBin(std::ostream &)const override;
	void toText(std::ostream &)const override;
};

#endif
