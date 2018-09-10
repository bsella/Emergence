#ifndef LUT_DIALOG_H
#define LUT_DIALOG_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "../Gradient.h"

class LutBackground:public QGraphicsItem{
public:
	LutBackground(Gradient*);
	int width,height;
private:
	const Gradient*grd;
	void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
	QRectF boundingRect()const;
};

class LutCursor:public QGraphicsItem{
public:
	LutCursor(const QColor &color);
	static void setDim(int w, int h);
private:
	static int height;
	static int width;
	const QColor color;
	Gradient::color* c;
	QRectF boundingRect()const;
	static const int cursorRadius=5;
	QVariant itemChange(GraphicsItemChange, const QVariant &);
	void paint(QPainter*,const QStyleOptionGraphicsItem*,QWidget*);
	void mousePressEvent(QGraphicsSceneMouseEvent*){}
	void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *);
	friend class LutView;
};

class LutView:public QGraphicsView{
public:
	LutView(QWidget* parent=0);
	~LutView();
private:
	QGraphicsScene* _scene;
	static LutCursor* curs;
	Gradient grd;
	LutBackground* background;
	void dragEnterEvent(QDragEnterEvent*);
	void dragLeaveEvent(QDragLeaveEvent*);
	void dragMoveEvent(QDragMoveEvent*);
	friend class LutDialog;
};

class LutDialog : public QDialog{
	Q_OBJECT
public:
	explicit LutDialog(QWidget *parent = 0);
	static Gradient *getGradient();
private:
	LutView* view;
	~LutDialog();
};

#endif // LUT_DIALOG_H
