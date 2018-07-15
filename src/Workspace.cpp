#include "Workspace.h"

Workspace::Workspace(QWidget *parent):QGraphicsView(parent){
	setAcceptDrops(true);
	setDragMode(DragMode::RubberBandDrag);
	setScene(new QGraphicsScene);
}

void Workspace::dragEnterEvent(QDragEnterEvent *event){
	QGraphicsView::dragEnterEvent(event);
	event->setAccepted(event->mimeData()->text()=="nodeTool");
}

void Workspace::dropEvent(QDropEvent *event){
	addNode((Node::Type)event->mimeData()->data("type").toInt(),
			mapToScene(event->pos()));
}

void Workspace::dragMoveEvent(QDragMoveEvent*){}

void Workspace::wheelEvent(QWheelEvent *event){
	if(event->delta()>0) scale(scaleFactor,scaleFactor);
	else scale(1/scaleFactor,1/scaleFactor);
}

void Workspace::addNode(Node::Type id){
	addNode(id,scene()->sceneRect().center());
}

void Workspace::addNode(Node::Type id, const QPointF& pos){
	Node* n= Node::nodeMalloc(id);
	if(!n) return;
	scene()->clearSelection();
	n->setPos(pos);
	n->initialPos=pos;
	connect(n,SIGNAL(moved()),this,SLOT(moveNodes()));
	connect(n,SIGNAL(connected(Node::Socket*,Node*)),this,SLOT(connectNode(Node::Socket*,Node*)));
	connect(n,SIGNAL(disconnected(Node::Socket*)),this,SLOT(disconnectNode(Node::Socket*)));
	connect(n->actionDelete,&QAction::triggered,this,[=](){undoStack.push(new DeleteNodeCommand(n,scene()));});
	undoStack.push(new AddNodeCommand(n,scene()));
}

void Workspace::addNodes(const QList<Node *> &n){
	undoStack.beginMacro("add_node");
	for(auto& i: n){
		if(!i) continue;
		i->initialPos=i->pos();
		connect(i,SIGNAL(moved()),this,SLOT(moveNodes()));
		connect(i,SIGNAL(connected(Node::Socket*,Node*)),this,SLOT(connectNode(Node::Socket*,Node*)));
		connect(i,SIGNAL(disconnected(Node::Socket*)),this,SLOT(disconnectNode(Node::Socket*)));
		connect(i->actionDelete,&QAction::triggered,this,[=](){undoStack.push(new DeleteNodeCommand(i,scene()));});
		undoStack.push(new AddNodeCommand(i,scene()));
	}
	undoStack.endMacro();
}

void Workspace::paste(){
	scene()->clearSelection();
	const QMimeData* mime= QApplication::clipboard()->mimeData();
	if(mime->text()=="Emergence_Nodes")
		addNodes(Node::binToNodes(mime->data("copy")));
}

void Workspace::select_all() const{
	for(auto& n : scene()->items())
		n->setSelected(true);
}

void Workspace::delete_selected(){
	undoStack.beginMacro("delete");
	for(auto& n:scene()->selectedItems())
		undoStack.push(new DeleteNodeCommand((Node*)n,scene()));
	undoStack.endMacro();
}

void Workspace::moveNodes(){
	undoStack.beginMacro("move");
	for(auto& n: scene()->selectedItems())
		undoStack.push(new MoveNodeCommand((Node*)n));
	undoStack.endMacro();
}

void Workspace::connectNode(Node::Socket* s, Node* n){
	undoStack.push(new ConnectNodeCommand(s,n));
}
void Workspace::disconnectNode(Node::Socket* s){
	undoStack.push(new DisconnectNodeCommand(s));
}

void Workspace::copy()const{
	QMimeData * mime=new QMimeData;
	mime->setText("Emergence_Nodes");
	mime->setData("copy",Node::nodesToBin(scene()->selectedItems()));
	QApplication::clipboard()->setMimeData(mime);
}

void Workspace::cut(){
	copy();
	delete_selected();
}
