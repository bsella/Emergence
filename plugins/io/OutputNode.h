#ifndef OutputNODE_H
#define OutputNODE_H

#include "Node.h"
#include <QDockWidget>

 class OutputNode : public Node{
public:
	OutputNode();
	~OutputNode();
	class RenderArea : public QDockWidget{
	public:
		RenderArea(OutputNode* node,QWidget* parent=0);
		QImage renderImage(int w,int h);
	private:
		OutputNode *start;
		void closeEvent(QCloseEvent *);
		void resizeEvent(QResizeEvent*);
		void paintEvent(QPaintEvent*);
	};
	inline static Node* makeNode(std::istream&){return new OutputNode;}
private slots:
	void updateOutput();
private:
	RenderArea *output;
	bool inside=true;
	uint outputNumber;
	static uint outputs;
	data_t kernel()const;
	void paint(QPainter* painter,
			   const QStyleOptionGraphicsItem* option,
			   QWidget* widget);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
	friend class ExportImageDialog;
};
#endif // RENDERNODE_H
