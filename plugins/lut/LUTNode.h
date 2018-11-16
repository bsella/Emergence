#ifndef LUTNODE_H
#define LUTNODE_H

#include "Gradient.h"
#include "Node.h"

class LUTNode:public Node{
public:
	explicit LUTNode(Gradient *p);
	static Node* makeFromBin(std::istream&);
	static Node* makeFromText(std::istream&);
private:
	void paint(QPainter* painter, const QStyleOptionGraphicsItem*option, QWidget*widget);
	data_t kernel()const;
	Gradient gradient;
	void toBin(std::ostream &)const override;
	void toText(std::ostream &)const override;
};

#endif
