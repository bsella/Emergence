#include "include/nodes/Node.h"
#include <iostream>

Node::Socket::Socket(unsigned i, double y, Node *parent):QGraphicsItem(parent),rank(i),iy(y){
	setZValue(parent->zValue()+1);
	setPos(-headSize-1,y);
	setAcceptedMouseButtons(Qt::LeftButton);
	setAcceptHoverEvents(true);
}

QRectF Node::Socket::boundingRect()const{
	return QRectF(-headSize,-headSize,headSize*2+1,headSize*2+1);
}

void Node::Socket::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
	painter->setPen(pen);
	painter->setRenderHint(QPainter::Antialiasing);
	painter->drawEllipse(boundingRect().center(),headSize,headSize);
}

void Node::Socket::hoverEnterEvent(QGraphicsSceneHoverEvent *){
	pen.setWidth(2);
	update();
}

void Node::Socket::hoverLeaveEvent(QGraphicsSceneHoverEvent *){
	pen.setWidth(1);
	update();
}

Node* Node::Socket::collidesWithNode() const{
	for(auto& i:collidingItems())
		if(i->data(0)=="node")
			return (Node*)i;
	return nullptr;
}

void Node::Socket::mouseMoveEvent(QGraphicsSceneMouseEvent*event){
	Node*i=collidesWithNode();
	if(i&&i!=parentItem()&&i->contains(event->scenePos()-i->scenePos())){
		hover=i;
		for(const auto& ii: i->collidingItems())
			if(i->zValue()<= ii->zValue())
				i->setZValue(ii->zValue()+1);
		QRectF r=i->boundingRect();
		parentItem()->setZValue(i->zValue());
		line->setZValue(i->zValue());
		setPos(i->pos()+QPoint(r.width()+Socket::headSize-1,r.height()/2)-parentItem()->pos());
	}else{
		hover=nullptr;
		setPos(event->scenePos()- boundingRect().center()-parentObject()->pos());
	}
	line->setLine(QLine(scenePos().toPoint()+QPoint(headSize,0),parentObject()->scenePos().toPoint()-QPoint(0,-iy)));
}

void Node::Socket::connectToNode(Node* n){
	Node* parent= (Node*)parentItem();
	if(n==parent) return;
	if(parent->nbArgs>=rank+1){
		parent->iNodes[rank]=n;
		n->oConnections.push_back({parent,rank});
		setVisible(false);
		line->setLine(QLine(scenePos().toPoint()+QPoint(-headSize,0),parentObject()->scenePos().toPoint()-QPoint(0,-iy)));
		parent->updateVal();
		emit parent->notifyRA();
	}
}

void Node::Socket::mousePressEvent(QGraphicsSceneMouseEvent*){
	if(!line) line=scene()->addLine(headSize,0,headSize,0);
}

void Node::Socket::mouseReleaseEvent(QGraphicsSceneMouseEvent*){
	if(hover) connectToNode(hover);
	else reset();
}

void Node::Socket::reset(){
	pen.setWidth(1);
	setVisible(true);
	setPos(-headSize-1,iy);
	scene()->removeItem(line);
	line=nullptr;
}

Node::Node(unsigned i, unsigned w, unsigned h, QColor c, uint n, bool spec):
	special(spec),id(i), width(w),height(h),color(c),pen(QPen(Qt::black,1)),nbArgs(n){
	setCursor(Qt::OpenHandCursor);
	setAcceptDrops(!spec);
	if(!spec)setData(0,"node");
	for(uint i=0; i<nbArgs;i++){
		sockets.push_back(new Socket(i,height*((i+1.0)/(nbArgs+1.0)),this));
		iNodes.push_back(nullptr);
	}
}

QRectF Node::boundingRect()const{
	if(special) return QRectF(0,0,width+socketSize,height);
	return QRectF(0,0,width+2*socketSize,height);
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem*,QWidget*){
	QRectF rect=boundingRect();
	if(!special)rect.setRight(rect.right()-socketSize);
	rect.setLeft(rect.left()+socketSize);
	painter->setRenderHint(QPainter::Antialiasing);
	QPainterPath path;
	path.addRoundedRect(rect, 10, 10);
	painter->setPen(pen);
	painter->fillPath(path, color);
	painter->drawPath(path);
	for(uint i=1; i<=nbArgs; i++)//draw input sockets
		painter->drawLine(rect.topLeft()+QPointF(0,i*height/(nbArgs+1.0)),rect.topLeft()+QPointF(-socketSize,i*rect.height()/(nbArgs+1.0)));
	if(!special)//draw output socket
		painter->drawLine(rect.center()+QPointF(rect.width()/2,0),rect.center()+QPointF(rect.width()/2+socketSize,0));
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
			sockets[i]->line->setLine(QLine(sockets[i]->line->line().p1().toPoint(),QPoint(x(),y()+r.height()*((i+1.0)/(iNodes.size()+1.0)))));
		}
		for(auto l=oConnections.begin(); l!=oConnections.end();++l)
			l->first->sockets[l->second]->line->setLine(QLine(QPoint(x()+r.width(),y()+r.height()/2),l->first->sockets[l->second]->line->line().p2().toPoint()));
	}
}

void Node::removeNode(){
	for(auto l=oConnections.begin(); l!=oConnections.end();){
		l->first->sockets[l->second]->reset();
		l->first->iNodes[l->second]=nullptr;
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

void Node::disconnectNode(unsigned rank){
	if(iNodes[rank]){
		emit addToWS(iNodes[rank]);
		for(auto l=iNodes[rank]->oConnections.begin(); l!=iNodes[rank]->oConnections.end();++l)
			if(l->first==this && l->second==rank){
				iNodes[rank]->oConnections.erase(l);
				break;
			}
		iNodes[rank]=nullptr;
		sockets[rank]->reset();
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
	painter->drawImage(width/2-icon.width()/2+socketSize,height/2-icon.height()/2,icon);
}

Node::~Node(){
	delete menu;
	for(auto& s : sockets)
		delete s;
}
