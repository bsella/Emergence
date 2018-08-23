#ifndef INPUTNODE_H
#define INPUTNODE_H

#include "Node.h"

class InputNode:public Node{
protected:
	InputNode(const std::string &);
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
	static double input_x, input_y;
	friend class OutputNode;
};

class XNode:public InputNode{
public:
	XNode();
	inline static Node* makeNode(std::istream&){return new XNode;}
private:
	void paint(QPainter* painter,
			   const QStyleOptionGraphicsItem* option,
			   QWidget* widget);
	inline data_t kernel()const{return input_x;}
};

class YNode:public InputNode{
public:
	YNode();
	inline static Node* makeNode(std::istream&){return new YNode;}
private:
	void paint(QPainter* painter,
				const QStyleOptionGraphicsItem* option,
				QWidget* widget);
	inline data_t kernel()const{return input_y;}
};

class RatioNode:public Node{
	void paint(QPainter* painter,
				const QStyleOptionGraphicsItem* option,
				QWidget* widget);
	static double ratio;
	inline data_t kernel()const{return ratio;}
	friend class OutputNode;
public:
	RatioNode();
	~RatioNode();
	inline static Node* makeNode(std::istream&){return new RatioNode;}
};

#endif
