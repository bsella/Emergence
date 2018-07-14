#ifndef LOGICNODE_H
#define LOGICNODE_H

#include "Node.h"

class LogicNode:public Node{
protected:
	LogicNode(unsigned i,unsigned n);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)=0;
};

class ORNode:public LogicNode{
public:
	ORNode();
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class ANDNode:public LogicNode{
public:
	ANDNode();
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class XORNode:public LogicNode{
public:
	XORNode();
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class NOTNode:public LogicNode{
public:
	NOTNode();
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif
