#ifndef FUNC_GATE_H
#define FUNC_GATE_H
#include "data_t.h"
#include "Gate.h"
#include "Socket.h"

#include <QDragEnterEvent>

class FuncGate:public Gate{
protected:
    FuncGate(unsigned w, unsigned h, QColor c= Qt::white, uint n=0, bool spec=false);
    std::vector<FuncGate*> input;
    std::vector<Socket*> sockets;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
public:
    bool special;
    QGraphicsLineItem *returnLine=nullptr;
    TypeEnum t=TypeEnum::ANY;
    virtual data_t eval()const=0;
    virtual void connect(FuncGate *g, unsigned i);
    operator bool();
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent*);
    void dropEvent(QGraphicsSceneDragDropEvent* event);
    unsigned int nbArgs;
};

#endif // FUNC_GATE_H
