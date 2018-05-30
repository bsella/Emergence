#ifndef NODE_H
#define NODE_H
#include <vector>

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
	struct Socket : public QGraphicsObject{
		Socket(unsigned i, double y, Node *parent);
		unsigned rank;
		double iy;
		bool visible=true;
		static const int headSize=8;
		bool connected=false;
		QPen pen=QPen(Qt::black);
		Node* hover;
		QGraphicsLineItem line;
		void connectToNode(Node*n);
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
	void updateVal();	//value is update (not valid)
	friend class Workspace;
public:
	unsigned id, width, height;
	data_t eval();
	virtual data_t kernel()const=0;
	operator bool();
signals:
	void notifyRA();
	void removeFromWS(Node* g);
	void addToWS(Node* g);
	void deleted();
private slots:
	void disconnectNode(unsigned rank);
protected slots:
	virtual void removeNode();
	void updateLines()const;
	void updateSelection();
protected:
	Node(unsigned i, unsigned w=50, unsigned h=50, QColor c=Qt::white,uint n=0, bool spec=false);
	~Node();

	static const int socketSize=5;
	data_t val;			//value returned by node
	bool validVal;		//value is valid
	QColor color;
	QMenu *menu=nullptr;
	QPen pen;
	uint nbArgs;
	std::vector<Node*> iNodes;		//INPUT NODES
	std::list<std::pair<Node*,uint>> oConnections;
	std::vector<Socket*> sockets;

	void updateOutputVal();
	QRectF boundingRect()const;
	virtual void paint(QPainter* painter,
			const QStyleOptionGraphicsItem* option,
			QWidget* widget);
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
	virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	void drawIcon(QPainter *painter, QString filename);

};

#endif
