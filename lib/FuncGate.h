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
private:
    unsigned int nbArgs;
    bool special;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent*);
    void dropEvent(QGraphicsSceneDragDropEvent* event);
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
private slots:
    void removeGate();
    void disconnectGate(unsigned rank);
protected:
    FuncGate(unsigned w, unsigned h, QColor c= Qt::white, uint n=0, bool spec=false);
    std::vector<FuncGate*> iGates;          //INPUT GATES
    FuncGate* oGate=nullptr;                //OUTPUT GATE
    unsigned int oRank;                     //OUTPUT RANK
    std::vector<QGraphicsLineItem*> lines;
    std::vector<Socket*> sockets;
    virtual void connectGate(FuncGate *g, unsigned i);
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
public:
    TypeEnum t=TypeEnum::ANY;
    virtual data_t eval()const=0;
    operator bool();
};

#endif // FUNC_GATE_H
