#ifndef BITMAPNODE_H
#define BITMAPNODE_H

#include <QPixmap>
#include <QFileDialog>
#include "Node.h"

class BitmapNode : public Node{
public:
	BitmapNode(const std::string &filename);
	~BitmapNode();
	void setBMP(const std::string &filename);
	std::string path;
	static Node* makeNode(void*);
private:
	QPixmap *bmp;
	int bmpWidth, bmpHeight;
	data_t kernel()const;
	void paint(QPainter *painter,
			   const QStyleOptionGraphicsItem* option,
			   QWidget* widget);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
	QImage scaleImage(uint w, uint h)const;
private slots:
	void changeBMP();
};

#endif // BITMAPNODE_H
