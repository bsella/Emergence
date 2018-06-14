#include "include/nodes/Node.h"
#include <iostream>

Node::Socket::Socket(unsigned i, double y, Node *parent):QGraphicsObject(parent)
	,rank(i),iy(y),line(headSize,0,headSize,0),parent(parent){
	setZValue(parent->zValue()+1);
	setPos(-headSize-1,y);
	setAcceptedMouseButtons(Qt::LeftButton);
	setAcceptHoverEvents(true);
	line.setParentItem(this);
	connect(this,&Node::Socket::xChanged,this,&Node::Socket::updateLine);
	connect(this,&Node::Socket::yChanged,this,&Node::Socket::updateLine);
}

QRectF Node::Socket::boundingRect()const{
	return QRectF(-headSize,-headSize,headSize*2+1,headSize*2+1);
}

void Node::Socket::updateLine(){
	line.setLine(QLine({headSize,0},(parentItem()->pos()-scenePos()-QPointF(0,-iy)).toPoint()));
}

void Node::Socket::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
	if(visible){
		painter->setPen(pen);
		painter->setRenderHint(QPainter::Antialiasing);
		painter->drawEllipse(boundingRect().center(),headSize,headSize);
	}
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
	if(i&&i!=parent&&i->contains(event->scenePos()-i->scenePos())){
		hover=i;
		for(const auto& ii: i->collidingItems())
			if(i->zValue()<= ii->zValue())
				i->setZValue(ii->zValue()+1);
		QRectF r=i->boundingRect();
		parent->setZValue(i->zValue());
		setZValue(i->zValue());
		setPos(i->pos()+QPoint(r.width()+Socket::headSize-1,r.height()/2)-parent->pos());
	}else{
		hover=nullptr;
		setPos(event->scenePos()- boundingRect().center()-parent->pos());
	}
}

void Node::Socket::connectToNode(Node* n){
	if(n==parent) return;
	if(parent->nbArgs>=rank+1 && !parent->iNodes[rank]){
		QRectF r= n->boundingRect();
		setPos(n->pos()+QPoint(r.width()-Socket::headSize,r.height()/2)-parent->pos());
		parent->iNodes[rank]=n;
		n->oConnections.push_back({parent,rank});
		connect(n,&Node::xChanged,this,&Node::Socket::updateLine);
		connect(n,&Node::yChanged,this,&Node::Socket::updateLine);
		setEnabled(false);
		visible=false;
		n->updateVal();
		parent->updateTopology();
	}
}

void Node::Socket::disconnectNode(){
	if(parent->iNodes[rank]){
		for(auto l=parent->iNodes[rank]->oConnections.begin();
			l!=parent->iNodes[rank]->oConnections.end();++l)
			if(l->first==parent && l->second==rank){
				parent->iNodes[rank]->oConnections.erase(l);
				break;
			}
		disconnect(parent->iNodes[rank],&Node::xChanged,this,&Node::Socket::updateLine);
		disconnect(parent->iNodes[rank],&Node::yChanged,this,&Node::Socket::updateLine);
		parent->iNodes[rank]=nullptr;
		reset();
		parent->updateTopology();
	}
}

void Node::Socket::mousePressEvent(QGraphicsSceneMouseEvent*){}

void Node::Socket::mouseReleaseEvent(QGraphicsSceneMouseEvent*){
	if(hover) emit parent->connected(this,hover);
	else reset();
}

void Node::Socket::reset(){
	pen.setWidth(1);
	visible=true;
	setEnabled(true);
	setPos(-headSize-1,iy);
	line.setLine(headSize,0,headSize,0);
}

Node* Node::Socket::hover;
SignalManager Node::sm;

double Node::x;
double Node::y;
double Node::ratio;

Node::Node(unsigned i, unsigned w, unsigned h, QColor c, uint n, bool spec):
	special(spec),id(i), width(w),height(h),color(c),pen(QPen(Qt::black,1)),nbArgs(n){
	setCursor(Qt::OpenHandCursor);
	if(!spec)setData(0,"node");
	for(uint i=0; i<nbArgs;i++){
		sockets.push_back(new Socket(i,height*((i+1.0)/(nbArgs+1.0)),this));
		iNodes.push_back(nullptr);
	}
	setFlags(GraphicsItemFlag::ItemIsMovable| GraphicsItemFlag::ItemIsSelectable);
	connect(this,SIGNAL(xChanged()),this,SLOT(updateLines()));
	connect(this,SIGNAL(yChanged()),this,SLOT(updateLines()));
	actionDelete=new QAction("Delete");
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
	pen.setWidth(isSelected()?2:1);
	painter->setPen(pen);
	painter->fillPath(path, color);
	painter->drawPath(path);
	for(uint i=1; i<=nbArgs; i++)//draw input sockets
		painter->drawLine(rect.topLeft()+QPointF(0,i*height/(nbArgs+1.0)),rect.topLeft()+QPointF(-socketSize,i*rect.height()/(nbArgs+1.0)));
	if(!special)//draw output socket
		painter->drawLine(rect.center()+QPointF(rect.width()/2,0),rect.center()+QPointF(rect.width()/2+socketSize,0));
}

void Node::updateLines()const{
	for(int i = 0; i<iNodes.size();i++)
		if(iNodes[i]){
			QRectF r= iNodes[i]->boundingRect();
			sockets[i]->setPos(iNodes[i]->pos()-pos()+QPointF(r.width()-Socket::headSize,r.height()/2));
		}
	for(auto l=oConnections.begin(); l!=oConnections.end();++l){
		QRectF r=boundingRect();
		l->first->sockets[l->second]->setPos(pos()-l->first->pos()+QPointF(r.width()-Socket::headSize,r.height()/2));
	}
}

QPointF Node::tmpPos;

void Node::mousePressEvent(QGraphicsSceneMouseEvent* event){
	if(event->button()==Qt::LeftButton){
		setCursor(Qt::ClosedHandCursor);
		setZValue(INT32_MAX);
	}else
		setCursor(Qt::ArrowCursor);
	tmpPos=pos();
	QGraphicsItem::mousePressEvent(event);
}
void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent*event){
	scene()->setSceneRect(scene()->itemsBoundingRect());
	setCursor(Qt::OpenHandCursor);
	setZValue(0);
	for(const auto& i: collidingItems())
		if(zValue()<= i->zValue())
			setZValue(i->zValue()+1);
	if(pos()-tmpPos!=QPointF(0,0))
		emit moved();
	QGraphicsItem::mouseReleaseEvent(event);
}

void Node::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
	if(!menu) menu= new QMenu;
	for(unsigned i = 0; i<nbArgs; i++){
		QAction *a= menu->addAction(QString("Disconnect ")+QString::number(i+1));
		a->setEnabled(iNodes[i]!=nullptr);
		connect(a,&QAction::triggered,this,[=](){emit disconnected(sockets[i]);});
	}
	menu->addSeparator();
	menu->addAction(actionDelete);
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

void Node::updateVal(){
	validVal=false;
	for(auto& i : oConnections)
		i.first->updateVal();
}

void Node::updateTopology(){
	for(auto& i : oConnections)
		i.first->updateTopology();
}

void Node::drawIcon(QPainter *painter, QString filename){
	QImage icon=QImage(filename);
	painter->drawImage(width/2-icon.width()/2+socketSize,height/2-icon.height()/2,icon);
}

data_t Node::eval(){
	if(validVal)return val;
	val = kernel();
	validVal=true;
	return val;
}
