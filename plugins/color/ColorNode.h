#ifndef COLORNODE_H
#define COLORNODE_H

#include "Node.h"
#include "data_t.h"

class ColorNode : public Node{
public:
	ColorNode(data_t::color c);
private:
	inline data_t kernel()const{return cache;}
	void paint(QPainter*,
	           const QStyleOptionGraphicsItem*,
	           QWidget*)=0;
	void contextMenuEvent(QGraphicsSceneContextMenuEvent*);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
private slots:
	void changeColor();
};

class RGBNode : public Node{
public:
	RGBNode();
private:
	data_t kernel()const;
	void paint(QPainter* painter,
					const QStyleOptionGraphicsItem*option,
					QWidget *widget);
};

class HSVNode : public Node{
public:
	HSVNode();
private:
	data_t kernel()const;
	void paint(QPainter* painter,
					const QStyleOptionGraphicsItem*option,
					QWidget *widget);
};
#endif // COLORNODE_H
