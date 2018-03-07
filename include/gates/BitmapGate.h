#ifndef BITMAPGATE_H
#define BITMAPGATE_H

#include <QPixmap>
#include <QFileDialog>
#include "Gate.h"

class BitmapGate : public Gate{
public:
	BitmapGate();
	~BitmapGate();
	BitmapGate(const QString& filename);
	void setBMP(const QString& filename);
private:
	QPixmap *bmp;
	int bmpWidth, bmpHeight;
	data_t eval();
	void paint(QPainter *painter,
			   const QStyleOptionGraphicsItem* option,
			   QWidget* widget);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
private slots:
	void changeBMP();
};

#endif // BITMAPGATE_H
