#ifndef RENDERPANEL_H
#define RENDERPANEL_H

#include "nodes/RenderNode.h"
#include "nodes/PixelNode.h"

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
	void resizeEvent(QResizeEvent*);
	QImage renderImage(int w, int h);
	bool isValid();
	PixelXNode * xg;
	PixelYNode * yg;
	RenderNode* start;
	RatioNode* ratio;
};

#endif
