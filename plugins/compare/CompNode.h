#ifndef COMPNODE_H
#define COMPNODE_H

#include "Node.h"

class CompNode:public Node{
protected:
	CompNode(const std::string &type);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*option, QWidget*widget)=0;
};

class GTNode:public CompNode{
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
	GTNode();
	static Node* makeNode(void*){return new GTNode;}
};

class LTNode:public CompNode{
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
	LTNode();
	static Node* makeNode(void*){return new LTNode;}
};

class EQNode:public CompNode{
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
	EQNode();
	static Node* makeNode(void*){return new EQNode;}
};

class NENode:public CompNode{
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
	NENode();
	static Node* makeNode(void*){return new NENode;}
};

#endif
