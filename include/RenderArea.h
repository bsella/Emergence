#ifndef RENDERPANEL_H
#define RENDERPANEL_H

#include "RenderGate.h"
#include "PixelGate.h"

#include <QWidget>
#include <QPainter>

class RenderArea : public QWidget {
	Q_OBJECT
signals:
	void valid(bool);
public:
	RenderArea(QWidget *parent=0);
	~RenderArea();
	void paintEvent(QPaintEvent*);
	QImage renderImage(int w, int h);
	bool isValid();
	PixelXGate * xg;
	PixelYGate * yg;
	RenderGate* start;
};

#endif
