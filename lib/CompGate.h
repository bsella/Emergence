#ifndef COMPGATE_H
#define COMPGATE_H

#include "FuncGate.h"

class CompGate:public FuncGate{
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*option, QWidget*widget);
    CompGate();
};

class GTGate:public CompGate{
public:
    data_t eval()const;
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class LTGate:public CompGate{
public:
    data_t eval()const;
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class GEGate:public CompGate{
public:
    data_t eval()const;
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class LEGate:public CompGate{
public:
    data_t eval()const;
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class EQGate:public CompGate{
public:
    data_t eval()const;
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class NEGate:public CompGate{
public:
    data_t eval()const;
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif
