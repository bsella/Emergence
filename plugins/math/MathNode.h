#ifndef MATHNODE_H
#define MATHNODE_H

#include "Node.h"

class MathNode:public Node{
protected:
	MathNode(const std::string &type, unsigned n, unsigned w=50, unsigned h=50);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)=0;
};

class ADDNode:public MathNode{
public:
	ADDNode();
	inline static Node* makeNode(std::istream&){return new ADDNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class SUBNode:public MathNode{
public:
	SUBNode();
	inline static Node* makeNode(std::istream&){return new SUBNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class MULNode:public MathNode{
public:
	MULNode();
	inline static Node* makeNode(std::istream&){return new MULNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class DIVNode:public MathNode{
public:
	DIVNode();
	inline static Node* makeNode(std::istream&){return new DIVNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class NEGNode:public MathNode{
public:
	NEGNode();
	inline static Node* makeNode(std::istream&){return new NEGNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class SQRTNode:public MathNode{
public:
	SQRTNode();
	inline static Node* makeNode(std::istream&){return new SQRTNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class ABSNode:public MathNode{
public:
	ABSNode();
	inline static Node* makeNode(std::istream&){return new ABSNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class LERPNode:public MathNode{
public:
	LERPNode();
	inline static Node* makeNode(std::istream&){return new LERPNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class CLAMPNode:public MathNode{
public:
	CLAMPNode();
	inline static Node* makeNode(std::istream&){return new CLAMPNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class SINNode:public MathNode{
public:
	SINNode();
	inline static Node* makeNode(std::istream&){return new SINNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class COSNode:public MathNode{
public:
	COSNode();
	inline static Node* makeNode(std::istream&){return new COSNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class MINNode:public MathNode{
public:
	MINNode();
	inline static Node* makeNode(std::istream&){return new MINNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class MAXNode:public MathNode{
public:
	MAXNode();
	inline static Node* makeNode(std::istream&){return new MAXNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class POWNode:public MathNode{
public:
	POWNode();
	inline static Node* makeNode(std::istream&){return new POWNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
class LOGNode:public MathNode{
public:
	LOGNode();
	inline static Node* makeNode(std::istream&){return new LOGNode;}
private:
	data_t kernel()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // MATHNODE_H
