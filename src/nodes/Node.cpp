#include "include/nodes/Node.h"
#include <iostream>

Node::Node(unsigned i, unsigned w, unsigned h, QColor c, uint n, bool spec):id(i), width(w),height(h),
	color(c),pen(QPen(Qt::black,1)), nbArgs(n),special(spec){
	setCursor(Qt::OpenHandCursor);
	setAcceptDrops(!spec);
	if(!spec)setData(0,"node");
	for(uint i=0; i<nbArgs;i++){
		sockets.push_back(new Socket(i,height*((i+1.0)/(nbArgs+1.0)),this));
		iNodes.push_back(nullptr);
		iLines.push_back(nullptr);
	}
}

QRectF Node::boundingRect()const{
	if(special) return QRectF(0,0,width+Socket::socketSize,height);
	return QRectF(0,0,width+2*Socket::socketSize,height);
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem*,QWidget*){
	QRectF rect=boundingRect();
	if(!special)rect.setRight(rect.right()-Socket::socketSize);
	rect.setLeft(rect.left()+Socket::socketSize);
	painter->setRenderHint(QPainter::Antialiasing);
	QPainterPath path;
	path.addRoundedRect(rect, 10, 10);
	painter->setPen(pen);
	painter->fillPath(path, color);
	painter->drawPath(path);
	for(uint i=1; i<=nbArgs; i++)//draw input sockets
		painter->drawLine(rect.topLeft()+QPointF(0,i*height/(nbArgs+1.0)),rect.topLeft()+QPointF(-Socket::socketSize,i*rect.height()/(nbArgs+1.0)));
	if(!special)//draw output socket
		painter->drawLine(rect.center()+QPointF(rect.width()/2,0),rect.center()+QPointF(rect.width()/2+Socket::socketSize,0));
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent* event){
	if(event->button()==Qt::LeftButton){
		setCursor(Qt::ClosedHandCursor);
		pen.setWidth(2);
	}else
		setCursor(Qt::ArrowCursor);
}
void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent*){
	this->scene()->setSceneRect(this->scene()->itemsBoundingRect());
	setCursor(Qt::OpenHandCursor);
	setZValue(0);
	for(const auto& i: collidingItems())
		if(zValue()<= i->zValue())
			setZValue(i->zValue()+1);
	pen.setWidth(1);
}
void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
	if(event->buttons()==Qt::LeftButton){
		setZValue(INT32_MAX);
		this->setPos(event->scenePos()- boundingRect().center());
		QRectF r= boundingRect();
		for(uint i = 0; i<iNodes.size();i++){
			if(iNodes[i]==nullptr)continue;
			iLines[i]->setLine(QLine(iLines[i]->line().p1().toPoint(),QPoint(x(),y()+r.height()*((i+1.0)/(iNodes.size()+1.0)))));
		}
		for(auto l=oConnections.begin(); l!=oConnections.end();++l)
			l->first->iLines[l->second]->setLine(QLine(QPoint(x()+r.width(),y()+r.height()/2),l->first->iLines[l->second]->line().p2().toPoint()));
	}
}

void Node::dragEnterEvent(QGraphicsSceneDragDropEvent *){
}

void Node::dropEvent(QGraphicsSceneDragDropEvent* ){
}

void Node::removeNode(){
	for(auto l=oConnections.begin(); l!=oConnections.end();){
		scene()->removeItem(l->first->iLines[l->second]);
		delete l->first->iLines[l->second];
		l->first->iLines[l->second]=nullptr;
		l->first->iNodes[l->second]=nullptr;
		l->first->sockets[l->second]->setVisible(true);
		l=oConnections.erase(l);
	}
	for(uint i=0; i<nbArgs;i++)
		disconnectNode(i);
	scene()->removeItem(this);
	emit notifyRA();
	emit removeFromWS(this);
}

void Node::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
	if(menu==nullptr)
		menu= new QMenu;
	for(unsigned i = 0; i<nbArgs; i++){
		QAction *a= menu->addAction(QString("Diconnect ")+QString::number(i+1));
		a->setEnabled(iNodes[i]!=nullptr);
		connect(a,&QAction::triggered,this,[=](){disconnectNode(i);});
	}
	menu->addSeparator();
	connect(menu->addAction("Delete"),&QAction::triggered,this,&Node::removeNode);
	menu->exec(event->screenPos());
	delete menu;
	menu=nullptr;
}

Node::operator bool(){
	for(auto g:iNodes)
		if(g==nullptr || !(*g))
			return false;
	return true;
}

void Node::connectNode(Node *g, unsigned i){
	if(g==this) return;
	if(nbArgs>=i+1){
		QRectF r= g->boundingRect();
		iLines[i]=this->scene()->addLine(g->x()+r.right(),g->y()+r.height()/2,
											x(),y()+height*((i+1.0)/(iNodes.size()+1.0)));
		iNodes[i]=g;
		g->oConnections.push_back({this,i});
		sockets[i]->setVisible(false);
		updateVal();
		emit notifyRA();
	}
}

void Node::disconnectNode(unsigned rank){
	if(iNodes[rank]){
		emit addToWS(iNodes[rank]);
		scene()->removeItem(iLines[rank]);
		delete iLines[rank];
		iLines[rank]=nullptr;
		for(auto l=iNodes[rank]->oConnections.begin(); l!=iNodes[rank]->oConnections.end();++l)
			if(l->first==this && l->second==rank){
				iNodes[rank]->oConnections.erase(l);
				break;
			}
		iNodes[rank]=nullptr;
		sockets[rank]->setVisible(true);
		updateVal();
		emit notifyRA();
	}
}

void Node::updateVal(){
	if(validVal){
		validVal=false;
		for(auto& i : oConnections)
			i.first->updateVal();
	}
}
void Node::updateOutputVal(){
	for(auto& i : oConnections)
		i.first->updateVal();
}

void Node::drawIcon(QPainter *painter, QString filename){
	QImage icon=QImage(filename);
	painter->drawImage(width/2-icon.width()/2+Socket::socketSize,height/2-icon.height()/2,icon);
}

Node::~Node(){
	delete menu;
	for(auto& s : sockets)
		delete s;
	for(auto& l : iLines)
		delete l;
}
