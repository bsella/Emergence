#ifndef FUNC_GATE_H
#define FUNC_GATE_H
#include "data_t.h"
#include "Gate.h"
#include "Socket.h"

#include <string>
#include <QAction>
#include <QMenu>
#include <QDragEnterEvent>

class FuncGate:public Gate{
protected slots:
	virtual void removeGate();
private slots:
	void disconnectGate(unsigned rank);
protected:
	FuncGate(unsigned w, unsigned h, const QColor& c= Qt::white, uint n=0, bool spec=false);
	unsigned int nbArgs;
	QMenu *menu=nullptr;
	std::vector<FuncGate*> iGates;          //INPUT GATES	
	std::vector<QGraphicsLineItem*> iLines;
	std::list<std::pair<FuncGate*,uint>> oConnections;
	std::vector<Socket*> sockets;
	void connectGate(FuncGate *g, unsigned i);
	virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
private:
	bool special;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
	void dragLeaveEvent(QGraphicsSceneDragDropEvent*);
	void dropEvent(QGraphicsSceneDragDropEvent* event);
public:
	TypeEnum t=TypeEnum::ANY;
	virtual data_t eval()const=0;
	operator bool();
};

#endif // FUNC_GATE_H
