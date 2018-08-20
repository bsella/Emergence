#include "Workspace.h"

Workspace::Workspace(QWidget *parent):QGraphicsScene(parent){}

void Workspace::dragEnterEvent(QGraphicsSceneDragDropEvent *event){
	QGraphicsScene::dragEnterEvent(event);
	event->accept();
}

void Workspace::dropEvent(QGraphicsSceneDragDropEvent *event){
	addNode(Node::nodeMalloc(event->mimeData()->data("type")),
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
	if(mime->text()=="Emergence_Nodes"){
		QList<Node*> nodes;
		std::istringstream istr(mime->data("copy").toStdString());
		istr >> nodes;
		addNodes(nodes);
	}
}

void Workspace::select_all() const{
	for(const auto& n : items())
		n->setSelected(true);
}

void Workspace::delete_selected(){
	bool found=false;
	for(auto& n:selectedItems()){
		if(((Node*)n)->_type!="output"&&((Node*)n)->_type!="input"){
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
	QList<Node*> nodes;
	for(const auto& i: selectedItems())
		nodes.append((Node*)i);
	std::ostringstream oss;
	oss << nodes;
	std::string str= oss.str();

	QByteArray ba(str.c_str(),str.length());
	mime->setData("copy",ba);
	QApplication::clipboard()->setMimeData(mime);
}

void Workspace::cut(){
	copy();
	delete_selected();
}

QList<Node*> Workspace::nodes()const{
	QList<Node*> ret;
	for(const auto& n:items())
		if(n->data(1)=="countMe")
			ret.append((Node*)n);
	return ret;
}
int Workspace::count()const{
	return nodes().size();
}
Node* Workspace::nodeAt(int i) const{
	return nodes().at(i);
}
int Workspace::nodeIndex(Node* n) const{
	return nodes().indexOf(n);
}

std::ostream& operator<<(std::ostream& out, const Workspace& w){
	out << w.nodes();
	return out;
}

std::istream& operator>>(std::istream& in, Workspace& w){
	QList<Node*> nodes;
	in>>nodes;
	w.addNodes(nodes);
	return in;
}

AddNodeCommand::AddNodeCommand(Node* node, QGraphicsScene* scene,
				QUndoCommand* parent): QUndoCommand(parent){
	_scene=scene;
	_node=node;
}
void AddNodeCommand::undo(){
	_node->setSelected(false);
	_scene->removeItem(_node);
	_scene->update();
}
void AddNodeCommand::redo(){
	_scene->addItem(_node);
	_node->setSelected(true);
	_node->setZValue(0);
	for(const auto& i: _node->collidingItems())
		if(_node->zValue()<= i->zValue())
			_node->setZValue(i->zValue()+1);
	_scene->update();
}
AddNodeCommand::~AddNodeCommand(){
	delete _node;
}

DeleteNodeCommand::DeleteNodeCommand(Node* node,QGraphicsScene *scene, QUndoCommand *parent):QUndoCommand(parent){
	_scene=scene;
	_node=node;
	iNodes=node->iNodes;
	oConnections=node->oConnections;
}
void DeleteNodeCommand::undo(){
	_scene->addItem(_node);
	for(int j=0; j<iNodes.size();j++)
		if(iNodes[j])
			_node->sockets[j]->connectToNode(iNodes[j]);
	for(int j=0; j<oConnections.size();j++)
		oConnections[j].first->sockets[oConnections[j].second]->connectToNode(_node);
	_scene->update();
}
void DeleteNodeCommand::redo(){
	for(auto& s:_node->sockets)
		s->disconnectNode();
	for(auto& c:_node->oConnections)
		c.first->sockets[c.second]->disconnectNode();
	_scene->removeItem(_node);
	_scene->update();
}

ConnectNodeCommand::ConnectNodeCommand(Node::Socket *s, Node *in,
					QUndoCommand *parent): QUndoCommand(parent){
	_socket=s;
	_iNode=in;
}
void ConnectNodeCommand::undo(){
	_socket->disconnectNode();
}
void ConnectNodeCommand::redo(){
	_socket->connectToNode(_iNode);
}

DisconnectNodeCommand::DisconnectNodeCommand(Node::Socket *s,
						QUndoCommand *parent): QUndoCommand(parent){
	_node=s->parent->iNodes[s->rank];
	_socket=s;
}
void DisconnectNodeCommand::undo(){
	_socket->connectToNode(_node);
}
void DisconnectNodeCommand::redo(){
	_socket->disconnectNode();
}

MoveNodeCommand::MoveNodeCommand(Node* node,
				QUndoCommand *parent): QUndoCommand(parent){
	_node=node;
	_pos=node->pos();
	_oldPos=node->initialPos;
}
void MoveNodeCommand::undo(){
	_node->setPos(_oldPos);
	_node->initialPos=_oldPos;
}
void MoveNodeCommand::redo(){
	_node->setPos(_pos);
	_node->initialPos=_pos;
}
