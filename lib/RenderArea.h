#ifndef RENDERPANEL_H
#define RENDERPANEL_H


#include "RenderGate.h"
#include "PixelGate.h"

#include <QWidget>
#include <QPainter>

class RenderArea : public QWidget {
public:
	RenderArea(QWidget *parent=0);
	~RenderArea();
	void paintEvent(QPaintEvent*);
	PixelXGate * xg;
	PixelYGate * yg;
	RenderGate* start;
private:
};

#endif
