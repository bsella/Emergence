#ifndef BITMAPGATE_H
#define BITMAPGATE_H

#include <QPixmap>
#include "Gate.h"

class BitmapGate : public Gate{
public:
	BitmapGate(QString filename);
private:
	data_t eval()const;
	void paint(QPainter *painter,
			   const QStyleOptionGraphicsItem* option,
			   QWidget* widget);
	QPixmap *bmp;
	int bmpWidth, bmpHeight;
};

#endif // BITMAPGATE_H
