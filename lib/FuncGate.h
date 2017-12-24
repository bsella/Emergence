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
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent*);
    void dropEvent(QGraphicsSceneDragDropEvent* event);
    unsigned int nbArgs;
private slots:
    void removeGate();
    void disconnectGate(unsigned rank);
protected:
    FuncGate(unsigned w, unsigned h, QColor c= Qt::white, uint n=0, bool spec=false);
    virtual void connectGate(FuncGate *g, unsigned i);
    std::vector<FuncGate*> input;
    std::vector<Socket*> sockets;
//    std::vector<QGraphicsLineItem*> lines;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
public:
    bool special;
    operator bool();
    QGraphicsLineItem* returnLine=nullptr;
    //std::pair<FuncGate*,uint> output={nullptr,0};
    TypeEnum t=TypeEnum::ANY;
    virtual data_t eval()const=0;
};

#endif // FUNC_GATE_H
