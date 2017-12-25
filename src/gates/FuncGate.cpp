#include "lib/FuncGate.h"
#include <iostream>

FuncGate::FuncGate(unsigned w, unsigned h, const QColor &c, uint n, bool spec):Gate(w,h,c),nbArgs(n),special(spec){
    setAcceptDrops(!spec);
    for(uint i=0; i<nbArgs;i++){
        sockets.push_back(new Socket(i,height*((i+1.0)/(nbArgs+1.0)),this));
        iGates.push_back(nullptr);
        lines.push_back(nullptr);
    }
}

void FuncGate::connectGate(FuncGate *g, unsigned i){
    if(nbArgs>=i+1){
        QRectF r= g->boundingRect();
        lines[i]=this->scene()->addLine(g->x()+r.right(),g->y()+r.height()/2,
                                             x(),y()+height*((i+1.0)/(iGates.size()+1.0)));
        iGates[i]=g;
        g->oGate=this;
        g->oRank=i;
        sockets[i]->setVisible(false);
        emit newConnectGate();
    }
}

void FuncGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Gate::paint(painter,option, widget);
    QRectF rect = boundingRect();
    rect.setLeft(rect.left()+socketSize); rect.setRight(rect.right()-socketSize);
    for(uint i=1; i<=nbArgs; i++)//draw input sockets
        painter->drawLine(rect.topLeft()+QPointF(0,i*height/(nbArgs+1.0)),rect.topLeft()+QPointF(-socketSize,i*rect.height()/(nbArgs+1.0)));
    if(!special)//draw output socket
        painter->drawLine(rect.center()+QPointF(rect.width()/2,0),rect.center()+QPointF(rect.width()/2+socketSize,0));
}

void FuncGate::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(event->buttons()==Qt::LeftButton){
        Gate::mouseMoveEvent(event);
        QRectF r= boundingRect();
        for(uint i = 0; i<iGates.size();i++){
            if(iGates[i]==nullptr)continue;
            lines[i]->setLine(QLine(lines[i]->line().p1().toPoint(),QPoint(x(),y()+r.height()*((i+1.0)/(iGates.size()+1.0)))));
        }
        if(oGate!=nullptr)
            oGate->lines[oRank]->setLine(QLine(QPoint(x()+r.width(),y()+r.height()/2),oGate->lines[oRank]->line().p2().toPoint()));
    }
}

void FuncGate::dragEnterEvent(QGraphicsSceneDragDropEvent* event){
    //if(event->mimeData()->parent()==this);
       //event;
    //else;
       //setAcceptDrops(true);
}

void FuncGate::dragLeaveEvent(QGraphicsSceneDragDropEvent*){
}

void FuncGate::dropEvent(QGraphicsSceneDragDropEvent* event){
    ((FuncGate*)(event->mimeData()->parent()))->connectGate(this,(event->mimeData()->data("rank")).toInt());
}

FuncGate::operator bool(){
    for(auto g:iGates)
        if(g==nullptr || !(*g))
            return false;
    return true;
}

void FuncGate::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
	if(menu==nullptr)
		menu= new QMenu;
	for(unsigned i = 0; i<nbArgs; i++){
        QAction *a= menu->addAction(QString("Diconnect ")+QString::number(i+1));
        a->setEnabled(iGates[i]!=nullptr);
        connect(a,&QAction::triggered,this,[=](){disconnectGate(i);});
    }
    menu->addSeparator();
	connect(menu->addAction("Delete"),&QAction::triggered,this,&FuncGate::removeGate);
	menu->exec(event->screenPos());
	menu=nullptr;
}

void FuncGate::removeGate(){
    for(uint i=0; i<nbArgs;i++)
        disconnectGate(i);
    if(oGate){
        scene()->removeItem(oGate->lines[oRank]);
        oGate->lines[oRank]=nullptr;
        oGate->sockets[oRank]->setVisible(true);
    }
    scene()->removeItem(this);
}

void FuncGate::disconnectGate(unsigned rank){
    if(iGates[rank]){
        scene()->removeItem(lines[rank]);
        iGates[rank]=nullptr;
        sockets[rank]->setVisible(true);
    }
}
