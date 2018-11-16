#ifndef REALNODE_H
#define REALNODE_H

#include "Node.h"

class RealNode:public Node{
public:
	RealNode(double v=0);
	static Node* makeFromBin(std::istream&);
	static Node* makeFromText(std::istream&);
private:
	inline data_t kernel()const{return cache;}
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*widget);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
	void toBin(std::ostream &)const override;
	void toText(std::ostream &)const override;
private slots:
	void changeNumber();
};

#endif
