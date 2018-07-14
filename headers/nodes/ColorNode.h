#ifndef COLORNODE_H
#define COLORNODE_H

#include "Node.h"
#include "data_t.h"

class ColorNode : public Node{
protected:
	ColorNode(unsigned i);
	virtual void paint(QPainter* painter,
					const QStyleOptionGraphicsItem*option,
					QWidget *widget)=0;
};

class RGBNode : public ColorNode{
public:
	RGBNode();
private:
	data_t kernel()const;
	void paint(QPainter* painter,
					const QStyleOptionGraphicsItem*option,
					QWidget *widget);
};

class HSVNode : public ColorNode{
public:
	HSVNode();
private:
	data_t kernel()const;
	void paint(QPainter* painter,
					const QStyleOptionGraphicsItem*option,
					QWidget *widget);
};
#endif // COLORNODE_H
