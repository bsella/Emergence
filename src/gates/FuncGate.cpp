#include "lib/FuncGate.h"
#include <iostream>

FuncGate::FuncGate(unsigned w, unsigned h, QColor c, uint n, bool spec):Gate(w,h,c),nbArgs(n),special(spec){
    setAcceptDrops(!spec);
    for(uint i=0; i<nbArgs;i++){
        sockets.push_back(new Socket(i,height*((i+1.0)/(nbArgs+1.0)),this));
        input.push_back(nullptr);
    }
}

void FuncGate::connect(FuncGate *g, unsigned i){
    if(input.size()>=i+1){
        QRectF r= g->boundingRect();
        g->returnLine=this->scene()->addLine(r.right(),g->y()+r.height()/2,
                                             x(),y()+height*((i+1.0)/(input.size()+1.0)));
        input[i]=g;
    }
    update();
}

void FuncGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Gate::paint(painter,option, widget);
    QRectF rect = boundingRect();
    rect.setLeft(rect.left()+socketSize); rect.setRight(rect.right()-socketSize);
    for(uint i=1; i<=nbArgs; i++){
        painter->drawLine(rect.topLeft()+QPointF(0,i*height/(nbArgs+1.0)),rect.topLeft()+QPointF(-socketSize,i*rect.height()/(nbArgs+1.0)));
        //sockets[i-1]->paint(painter,option,widget);
    }
    if(!special)
        painter->drawLine(rect.center()+QPointF(rect.width()/2,0),rect.center()+QPointF(rect.width()/2+socketSize,0));
}

void FuncGate::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(event->buttons()==Qt::LeftButton){
        Gate::mouseMoveEvent(event);
        QRectF r= boundingRect();
        for(uint i = 0; i<input.size();i++){
            if(input[i]==nullptr)continue;
            input[i]->returnLine->setLine(QLine(input[i]->returnLine->line().p1().toPoint(),QPoint(x(),y()+r.height()*((i+1.0)/(input.size()+1.0)))));
        }
        if(returnLine!=nullptr)
            returnLine->setLine(QLine(QPoint(x()+r.width(),y()+r.height()/2),returnLine->line().p2().toPoint()));
    }
}

void FuncGate::dragEnterEvent(QGraphicsSceneDragDropEvent* event){
    /*if(event->mimeData()->parent()==this)
        setAcceptDrops(false);
    else
        setAcceptDrops(true);*/
}

void FuncGate::dragLeaveEvent(QGraphicsSceneDragDropEvent*){
}

void FuncGate::dropEvent(QGraphicsSceneDragDropEvent* event){
    ((FuncGate*)(event->mimeData()->parent()))->connect(this,(event->mimeData()->data("rank")).toInt());
}

FuncGate::operator bool(){
    for(auto g:input)
        if(g==nullptr || !(*g))
            return false;
    return true;
}
