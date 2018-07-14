#ifndef MATHNODE_H
#define MATHNODE_H

#include <QtMath>
#include "Node.h"

class MathNode:public Node{
protected:
	MathNode(unsigned i, unsigned n, unsigned w=50, unsigned h=50);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)=0;
};

class ADDNode:public MathNode{
public:
	ADDNode();
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class SUBNode:public MathNode{
public:
	SUBNode();
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class MULNode:public MathNode{
public:
	MULNode();
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class DIVNode:public MathNode{
public:
	DIVNode();
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class NEGNode:public MathNode{
public:
	NEGNode();
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class SQRTNode:public MathNode{
public:
	SQRTNode();
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class ABSNode:public MathNode{
public:
	ABSNode();
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class LERPNode:public MathNode{
public:
	LERPNode();
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class CLAMPNode:public MathNode{
public:
	CLAMPNode();
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class SINNode:public MathNode{
public:
	SINNode();
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class COSNode:public MathNode{
public:
	COSNode();
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class MINNode:public MathNode{
public:
	MINNode();
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class MAXNode:public MathNode{
public:
	MAXNode();
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // MATHNODE_H
