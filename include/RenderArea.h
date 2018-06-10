#ifndef RENDERPANEL_H
#define RENDERPANEL_H

#include "nodes/PixelNode.h"
#include "nodes/RenderNode.h"

#include <QWidget>
#include <QPainter>

class RenderArea : public QWidget {
public:
	RenderArea(QWidget *parent=0);
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
	QImage renderImage(int w, int h);
	PixelXNode * xg;
	PixelYNode * yg;
	RenderNode * start;
	RatioNode* ratio;
};

#endif
