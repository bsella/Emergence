#ifndef COMPNODE_H
#define COMPNODE_H

#include "Node.h"

class CompNode:public Node{
protected:
	CompNode(Type i);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*option, QWidget*widget)=0;
};

class GTNode:public CompNode{
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
	GTNode();
};

class LTNode:public CompNode{
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
	LTNode();
};

class EQNode:public CompNode{
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
	EQNode();
};

class NENode:public CompNode{
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
	NENode();
};

#endif
