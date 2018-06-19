#ifndef RENDERNODE_H
#define RENDERNODE_H

#include "Node.h"
#include <QDockWidget>

class RenderNode : public Node{
public:
	RenderNode();
	~RenderNode();
	class RenderArea : public QDockWidget{
	public:
		RenderArea(RenderNode* node,QWidget* parent=0);
		QImage renderImage(int w,int h);
	private:
		RenderNode *start;
		void closeEvent(QCloseEvent *);
		void resizeEvent(QResizeEvent*);
		void paintEvent(QPaintEvent*);
	};
private:
	RenderArea *output;
	bool inside=true;
	uint outputNumber;
	static uint outputs;
	data_t kernel()const;
	void updateTopology();
	void paint(QPainter* painter,
			   const QStyleOptionGraphicsItem* option,
			   QWidget* widget);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
	friend class ExportImageDialog;
};

#endif // RENDERNODE_H
