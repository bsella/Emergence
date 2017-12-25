#ifndef RENDERPANEL_H
#define RENDERPANEL_H

#include "RenderGate.h"
#include "PixelGate.h"

#include <QWidget>
#include <QPainter>

class RenderArea : public QWidget {
	//Q_OBJECT
public:
	RenderArea(QWidget *parent=0);
	virtual ~RenderArea();
	void paintEvent(QPaintEvent*);
	PixelXGate * xg;
	PixelYGate * yg;
	RenderGate* start;
private:
public slots:
	void lol(){}
};

#endif
