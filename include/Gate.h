#ifndef GATE_H
#define GATE_H
#include <vector>

#include <QGraphicsObject>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QGraphicsScene>
#include <QMenu>

#include "data_t.h"
#include "Socket.h"

#define BOOL_G		1
#define DOUBLE_G	2
#define COLOR_G		3
#define IF_G		4
#define PALETTE_G	5
#define GT_G		6
#define LT_G		7
#define EQ_G		8
#define NE_G		9
#define OR_G		10
#define AND_G		11
#define XOR_G		12
#define NOT_G		13
#define X_G			14
#define Y_G			15
#define RENDER_G	16
#define ADD_G		17
#define SUB_G		18
#define MUL_G		19
#define DIV_G		20
#define NEG_G		21
#define SQRT_G		22
#define ABS_G		23
#define LERP_G		24
#define CLAMP_G		25
#define BITMAP_G	26
#define SIN_G		27
#define COS_G		28
#define MIN_G		29
#define MAX_G		30

class Gate: public QGraphicsObject{
	Q_OBJECT
public:
	~Gate();
	unsigned id, width, height;
	virtual data_t eval()const=0;
	operator bool();
signals:
	void notifyRA();
	void removeFromWS(Gate* g);
	void addToWS(Gate* g);
	void deleted();
private slots:
	void disconnectGate(unsigned rank);
protected slots:
	virtual void removeGate();
protected:
	QMenu *menu=nullptr;
	QColor color;
	Gate(unsigned i, unsigned w=50, unsigned h=50, QColor c=Qt::white,uint n=0, bool spec=false);
	virtual void paint(QPainter* painter,
			   const QStyleOptionGraphicsItem* option,
			   QWidget* widget);
	QPen pen;
	QRectF boundingRect()const;
	uint nbArgs;
	static const int socketSize=5;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	std::vector<Gate*> iGates;          //INPUT GATES
	std::vector<QGraphicsLineItem*> iLines;
	std::list<std::pair<Gate*,uint>> oConnections;
	std::vector<Socket*> sockets;
	virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	void dropEvent(QGraphicsSceneDragDropEvent *event);
	void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
	void connectGate(Gate *g, unsigned i);
	void drawIcon(QPainter *painter, QString filename);
private:
	bool special;
	friend class Workspace;
};

#endif
