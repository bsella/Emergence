#ifndef LOGICNODE_H
#define LOGICNODE_H

#include "Node.h"

class LogicNode:public Node{
protected:
	LogicNode(const std::string &type, unsigned n);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)=0;
};

class ORNode:public LogicNode{
public:
	ORNode();
	inline static Node* makeNode(std::istream&){return new ORNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class ANDNode:public LogicNode{
public:
	ANDNode();
	inline static Node* makeNode(std::istream&){return new ANDNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class XORNode:public LogicNode{
public:
	XORNode();
	inline static Node* makeNode(std::istream&){return new XORNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class NOTNode:public LogicNode{
public:
	NOTNode();
	inline static Node* makeNode(std::istream&){return new NOTNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif
