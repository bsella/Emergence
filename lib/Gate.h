#ifndef GATE_H
#define GATE_H
#include <vector>

#include <QGraphicsObject>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QGraphicsScene>

#include "data_t.h"

class Gate: public QGraphicsObject{
public:
    unsigned int width, height;
    QRectF boundingRect() const;
signals:
    void newConnectGate(){}

protected:
    QColor color;
    Gate(unsigned w=50, unsigned h=50, QColor c=Qt::white);
    virtual void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget);
    QPen pen;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    static const int socketSize=5;
};

#endif
