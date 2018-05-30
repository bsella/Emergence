#ifndef PXYNODE_H
#define PXYNODE_H

#include "Node.h"

class PixelNode:public Node{
public:
		void update(double i);
protected:
		PixelNode(unsigned i);
		virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
private:
		inline data_t kernel()const{return val;}
		void removeNode();
};

class PixelXNode:public PixelNode{
		void paint(QPainter* painter,
				   const QStyleOptionGraphicsItem* option,
				   QWidget* widget);
public:
		PixelXNode();
};

class PixelYNode:public PixelNode{
	void paint(QPainter* painter,
				const QStyleOptionGraphicsItem* option,
				QWidget* widget);
public:
	PixelYNode();
};

class RatioNode:public PixelNode{
	void paint(QPainter* painter,
				const QStyleOptionGraphicsItem* option,
				QWidget* widget);
public:
	RatioNode();
	void update(unsigned x, unsigned y);
};

#endif
