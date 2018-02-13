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

class Gate: public QGraphicsObject{
	Q_OBJECT
public:
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
	~Gate();
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
