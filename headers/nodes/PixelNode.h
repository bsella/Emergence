#ifndef PXYNODE_H
#define PXYNODE_H

#include "Node.h"

class PixelNode:public Node{
protected:
		PixelNode(Type i);
		virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
};

class PixelXNode:public PixelNode{
		void paint(QPainter* painter,
				   const QStyleOptionGraphicsItem* option,
				   QWidget* widget);
		inline data_t kernel()const{return Node::x;}
public:
		PixelXNode();
};

class PixelYNode:public PixelNode{
	void paint(QPainter* painter,
				const QStyleOptionGraphicsItem* option,
				QWidget* widget);
	inline data_t kernel()const{return Node::y;}
public:
	PixelYNode();
};

class RatioNode:public Node{
	void paint(QPainter* painter,
				const QStyleOptionGraphicsItem* option,
				QWidget* widget);
	inline data_t kernel()const{return Node::ratio;}
public:
	RatioNode();
	~RatioNode();
};

#endif
