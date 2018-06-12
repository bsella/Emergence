#ifndef NODE_H
#define NODE_H

#include <QGraphicsObject>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QGraphicsScene>
#include <QMenu>

#include "include/data_t.h"

#define DOUBLE_G	1
#define COLOR_G		2
#define IF_G		3
#define PALETTE_G	4
#define GT_G		5
#define LT_G		6
#define EQ_G		7
#define NE_G		8
#define OR_G		9
#define AND_G		10
#define XOR_G		11
#define NOT_G		12
#define X_G			13
#define Y_G			14
#define RENDER_G	15
#define ADD_G		16
#define SUB_G		17
#define MUL_G		18
#define DIV_G		19
#define NEG_G		20
#define SQRT_G		21
#define ABS_G		22
#define LERP_G		23
#define CLAMP_G		24
#define BITMAP_G	25
#define SIN_G		26
#define COS_G		27
#define MIN_G		28
#define MAX_G		29
#define RGB_G		30
#define HSV_G		31
#define RATIO_G		32
#define CPLX_G		33

class Node: public QGraphicsObject{
	Q_OBJECT
private:
	friend class MainWindow;
	friend class DeleteNodeCommand;
	friend class ConnectNodeCommand;
	friend class DisconnectNodeCommand;
	friend class MoveNodeCommand;
	struct Socket : public QGraphicsObject{
		Socket(unsigned i, double y, Node *parent);
		unsigned rank;
		double iy;
		bool visible=true;
		static const int headSize=8;
		QPen pen=QPen(Qt::black);
		QGraphicsLineItem line;
		Node *hover, *parent;
		void connectToNode(Node*n);
		void disconnectNode();
		QRectF boundingRect() const;
		void updateLine();
		Node* collidesWithNode()const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
		void hoverEnterEvent(QGraphicsSceneHoverEvent*);
		void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
		void mouseMoveEvent(QGraphicsSceneMouseEvent*);
		void mousePressEvent(QGraphicsSceneMouseEvent*);
		void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
		void reset();
	};
	bool special;
	QPointF initialPos;
	static QPointF tmpPos;
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
public:
	Node(unsigned i, unsigned w=50, unsigned h=50, QColor c=Qt::white,uint n=0, bool spec=false);
	unsigned id, width, height;
	data_t eval();
	virtual data_t kernel()const=0;
	operator bool();
signals:
	void connected(Node::Socket* s,Node* n);
	void disconnected(Node::Socket* s);
	void notifyRA();
	void moved();
protected slots:
	void updateLines()const;
protected:
	static const int socketSize=5;
	virtual void updateVal();	//value is update (not valid)
	data_t val;			//value returned by node
	bool validVal;		//value is valid
	QColor color;
	QMenu *menu=nullptr;
	QPen pen;
	uint nbArgs;
	QVector<Node*> iNodes;		//INPUT NODES
	QList<QPair<Node*,uint>> oConnections;
	QVector<Socket*> sockets;

	virtual void updateTopology();
	QRectF boundingRect()const;
	virtual void paint(QPainter* painter,
			const QStyleOptionGraphicsItem* option,
			QWidget* widget);
	virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	void drawIcon(QPainter *painter, QString filename);
};

#endif
