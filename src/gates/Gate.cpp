#include "include/Gate.h"
#include <iostream>

Gate::Gate(unsigned i, unsigned w, unsigned h, QColor c, uint n, bool spec):id(i), width(w),height(h),
	color(c),pen(QPen(Qt::black,1)), nbArgs(n),special(spec){
	setCursor(Qt::OpenHandCursor);
	setAcceptDrops(!spec);
	for(uint i=0; i<nbArgs;i++){
		sockets.push_back(new Socket(i,height*((i+1.0)/(nbArgs+1.0)),this));
		iGates.push_back(nullptr);
		iLines.push_back(nullptr);
	}
}

QRectF Gate::boundingRect()const{
    return QRectF(0,0,width+2*socketSize,height);
}

void Gate::paint(QPainter* painter, const QStyleOptionGraphicsItem*,QWidget*){
    QRectF rect=boundingRect();
    rect.setLeft(rect.left()+socketSize); rect.setRight(rect.right()-socketSize);
    painter->setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRoundedRect(rect, 10, 10);
    painter->setPen(pen);
    painter->fillPath(path, color);
	painter->drawPath(path);
	rect = boundingRect();
	rect.setLeft(rect.left()+socketSize); rect.setRight(rect.right()-socketSize);
	for(uint i=1; i<=nbArgs; i++)//draw input sockets
		painter->drawLine(rect.topLeft()+QPointF(0,i*height/(nbArgs+1.0)),rect.topLeft()+QPointF(-socketSize,i*rect.height()/(nbArgs+1.0)));
	if(!special)//draw output socket
		painter->drawLine(rect.center()+QPointF(rect.width()/2,0),rect.center()+QPointF(rect.width()/2+socketSize,0));
}

void Gate::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if(event->button()==Qt::LeftButton){
        setCursor(Qt::ClosedHandCursor);
        pen.setWidth(2);
    }else
        setCursor(Qt::ArrowCursor);
}
void Gate::mouseReleaseEvent(QGraphicsSceneMouseEvent*){
    this->scene()->setSceneRect(this->scene()->itemsBoundingRect());
    setCursor(Qt::OpenHandCursor);
    setZValue(0);
    for(const auto& i: collidingItems())
        if(zValue()<= i->zValue())
            setZValue(i->zValue()+1);
    pen.setWidth(1);
}
void Gate::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(event->buttons()==Qt::LeftButton){
        setZValue(INT32_MAX);
        this->setPos(event->scenePos()- boundingRect().center());
		QRectF r= boundingRect();
		for(uint i = 0; i<iGates.size();i++){
			if(iGates[i]==nullptr)continue;
			iLines[i]->setLine(QLine(iLines[i]->line().p1().toPoint(),QPoint(x(),y()+r.height()*((i+1.0)/(iGates.size()+1.0)))));
		}
		for(auto l=oConnections.begin(); l!=oConnections.end();++l)
			l->first->iLines[l->second]->setLine(QLine(QPoint(x()+r.width(),y()+r.height()/2),l->first->iLines[l->second]->line().p2().toPoint()));
	}
}

void Gate::dragEnterEvent(QGraphicsSceneDragDropEvent *event){
	if(event->mimeData()->parent()==this)
		setAcceptDrops(false);
	else
		setAcceptDrops(!special);
}

void Gate::dropEvent(QGraphicsSceneDragDropEvent* event){
	if(event->mimeData()->data("socket")=="1")
		((Gate*)(event->mimeData()->parent()))->connectGate(this,(event->mimeData()->data("rank")).toInt());
}

void Gate::removeGate(){
	for(auto l=oConnections.begin(); l!=oConnections.end();){
		scene()->removeItem(l->first->iLines[l->second]);
		l->first->iLines[l->second]=nullptr;
		l->first->iGates[l->second]=nullptr;
		l->first->sockets[l->second]->setVisible(true);
		l=oConnections.erase(l);
	}
	for(uint i=0; i<nbArgs;i++)
		disconnectGate(i);
	scene()->removeItem(this);
	emit notifyRA();
	emit removeFromWS(this);
}

void Gate::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
	if(menu==nullptr)
		menu= new QMenu;
	for(unsigned i = 0; i<nbArgs; i++){
		QAction *a= menu->addAction(QString("Diconnect ")+QString::number(i+1));
		a->setEnabled(iGates[i]!=nullptr);
		connect(a,&QAction::triggered,this,[=](){disconnectGate(i);});
	}
	menu->addSeparator();
	connect(menu->addAction("Delete"),&QAction::triggered,this,&Gate::removeGate);
	menu->exec(event->screenPos());
	menu=nullptr;
}

Gate::operator bool(){
	for(auto g:iGates)
		if(g==nullptr || !(*g))
			return false;
	return true;
}

void Gate::connectGate(Gate *g, unsigned i){
	if(g==this) return;
	if(nbArgs>=i+1){
		QRectF r= g->boundingRect();
		iLines[i]=this->scene()->addLine(g->x()+r.right(),g->y()+r.height()/2,
											x(),y()+height*((i+1.0)/(iGates.size()+1.0)));
		iGates[i]=g;
		g->oConnections.push_back({this,i});
		sockets[i]->setVisible(false);
		emit notifyRA();
	}
}

void Gate::disconnectGate(unsigned rank){
	if(iGates[rank]){
		emit addToWS(iGates[rank]);
		scene()->removeItem(iLines[rank]);
		iLines[rank]=nullptr;
		for(auto l=iGates[rank]->oConnections.begin(); l!=iGates[rank]->oConnections.end();++l)
			if(l->first==this){
				iGates[rank]->oConnections.erase(l);
				break;
			}
		iGates[rank]=nullptr;
		sockets[rank]->setVisible(true);
		emit notifyRA();
	}
}

void Gate::drawIcon(QPainter *painter, QString filename){
	QImage icon=QImage(filename);
	painter->drawImage(width/2-icon.width()/2+socketSize,height/2-icon.height()/2,icon);
}
