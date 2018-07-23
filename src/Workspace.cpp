#include "Workspace.h"
#include "commands.h"

Workspace::Workspace(QWidget *parent):QGraphicsScene(parent){}

void Workspace::putXYandOutput(){
	Node* y= Node::nodeMalloc(Node::Type::Y_G);
	y->setPos(0,100);
	y->initialPos={0,100};
	Node* out= Node::nodeMalloc(Node::Type::RENDER_G);
	out->setPos(100,50);
	out->initialPos={100,50};
	QList<Node*> initList;
	initList.append(Node::nodeMalloc(Node::Type::X_G));
	initList.append(y);
	initList.append(out);
	addNodes(initList);
	clearSelection();
}

void Workspace::dragEnterEvent(QGraphicsSceneDragDropEvent *event){
	QGraphicsScene::dragEnterEvent(event);
	event->accept();
}

void Workspace::dropEvent(QGraphicsSceneDragDropEvent *event){
	addNode(Node::nodeMalloc((Node::Type)event->mimeData()->data("type").toInt()),
			event->scenePos());
}

void Workspace::dragMoveEvent(QGraphicsSceneDragDropEvent*event){
	QGraphicsScene::dragMoveEvent(event);
	event->accept();
}

void Workspace::addNode(Node* n){
	addNode(n,sceneRect().center());
}

void Workspace::addNode(Node *n, const QPointF& pos){
	if(!n) return;
	clearSelection();
	n->setPos(pos);
	n->initialPos=pos;
	connect(n,SIGNAL(moved()),this,SLOT(moveNodes()));
	connect(n,SIGNAL(connected(Node::Socket*,Node*)),this,SLOT(connectNode(Node::Socket*,Node*)));
	connect(n,SIGNAL(disconnected(Node::Socket*)),this,SLOT(disconnectNode(Node::Socket*)));
	connect(n->actionDelete,&QAction::triggered,this,[=](){undoStack.push(new DeleteNodeCommand(n,this));});
	undoStack.push(new AddNodeCommand(n,this));
}

void Workspace::addNodes(const QList<Node *> &n){
	undoStack.beginMacro("add_node");
	for(auto& i: n){
		if(!i) continue;
		i->initialPos=i->pos();
		connect(i,SIGNAL(moved()),this,SLOT(moveNodes()));
		connect(i,SIGNAL(connected(Node::Socket*,Node*)),this,SLOT(connectNode(Node::Socket*,Node*)));
		connect(i,SIGNAL(disconnected(Node::Socket*)),this,SLOT(disconnectNode(Node::Socket*)));
		connect(i->actionDelete,&QAction::triggered,this,[=](){undoStack.push(new DeleteNodeCommand(i,this));});
		undoStack.push(new AddNodeCommand(i,this));
	}
	undoStack.endMacro();
}

void Workspace::paste(){
	clearSelection();
	const QMimeData* mime= QApplication::clipboard()->mimeData();
	if(mime->text()=="Emergence_Nodes")
		addNodes(Node::binToNodes(mime->data("copy")));
}

void Workspace::select_all() const{
	for(auto& n : items())
		n->setSelected(true);
}

void Workspace::delete_selected(){
	bool found=false;
	for(auto& n:selectedItems()){
		if(((Node*)n)->id!=Node::OUTPUT_G&&((Node*)n)->id!=Node::INPUT_G){
			if(!found) undoStack.beginMacro("delete");
			found=true;
			undoStack.push(new DeleteNodeCommand((Node*)n,this));
		}
	}
	if(found)undoStack.endMacro();
}

void Workspace::moveNodes(){
	undoStack.beginMacro("move");
	for(auto& n: selectedItems())
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
	mime->setData("copy",Node::nodesToBin(selectedItems()));
	QApplication::clipboard()->setMimeData(mime);
}

void Workspace::cut(){
	copy();
	delete_selected();
}
