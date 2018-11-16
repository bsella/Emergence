#ifndef COLORNODE_H
#define COLORNODE_H

#include "Node.h"
#include "data_t.h"

class ColorNode : public Node{
public:
	ColorNode(const data_t::color& c= 0xff000000);
	static Node* makeFromBin(std::istream&);
	static Node* makeFromText(std::istream&);
private:
	inline data_t kernel()const{return cache;}
	void paint(QPainter*,
			   const QStyleOptionGraphicsItem*,
			   QWidget*);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent*);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*)override;
	void changeColor();
	void toBin(std::ostream&)const override;
	void toText(std::ostream&)const override;
};

class RGBNode : public Node{
public:
	RGBNode();
	inline static Node* makeNode(std::istream&){return new RGBNode;}
private:
	data_t kernel()const;
	void paint(QPainter* painter,
					const QStyleOptionGraphicsItem*option,
					QWidget *widget);
};

class HSVNode : public Node{
public:
	HSVNode();
	inline static Node* makeNode(std::istream&){return new HSVNode;}
private:
	data_t kernel()const;
	void paint(QPainter* painter,
					const QStyleOptionGraphicsItem*option,
					QWidget *widget);
};
#endif // COLORNODE_H
