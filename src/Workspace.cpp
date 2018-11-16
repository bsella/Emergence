#include "Workspace.h"

#include <QClipboard>
#include <QMimeData>
#include <QApplication>
#include <QGraphicsSceneDragDropEvent>

#include "NodeBox.h"

Workspace::Workspace(QWidget *parent):QGraphicsScene(parent){}

void Workspace::dragEnterEvent(QGraphicsSceneDragDropEvent *event){
	QGraphicsScene::dragEnterEvent(event);
	event->accept();
}

void Workspace::dropEvent(QGraphicsSceneDragDropEvent *event){
	NodeTool::workspace=this;
	NodeTool::point=event->scenePos();
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
	QList<Node*> selectedNodes;
	for(const auto& i: selectedItems())
		selectedNodes.append((Node*)i);
	std::ostringstream oss;
	int tmp=selectedNodes.size();
	oss.write(reinterpret_cast<const char*>(&tmp),sizeof(int));
	for(const auto& n:selectedNodes)
		n->toBin(oss);
	for(const auto& n:selectedNodes)
		for(const auto& nn:n->iNodes){
			tmp= selectedNodes.indexOf(nn);
			oss.write(reinterpret_cast<const char*>(&tmp),sizeof(int));
		}
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
void Workspace::toBin(std::ostream& out) const{
	int tmp=nodes().size();
	out.write(reinterpret_cast<const char*>(&tmp),sizeof(int));
	for(const auto& n:nodes())
		n->toBin(out);
	for(const auto& n:nodes())
		for(const auto& nn:n->iNodes){
			tmp= nodes().indexOf(nn);
			out.write(reinterpret_cast<const char*>(&tmp),sizeof(int));
		}
}
void Workspace::toText(std::ostream& out) const{
	out << nodes().size()<< '\n';
	for(const auto& n:nodes()){
		n->toText(out);
		out << '\n';
	}
	for(const auto& n:nodes())
		for(const auto& nn:n->iNodes)
			out << nodes().indexOf(nn) << ' ';
	out << '\n';
}

void Workspace::fromBin(std::istream& in){
	QList<Node*> nodes;
	in >> nodes;
	addNodes(nodes);
}
void Workspace::fromText(std::istream& in){
	QList<Node*> nodes;
	int tmp;
	in>>tmp;

	for(int i=0;i<tmp;i++){
		std::string type;
		int xx,yy;
		in >> type >>xx >> yy;
		Node* n;
		n= Node::makeNodeMethods[type](in);
		n->setPos(xx,yy);
		nodes.push_back(n);
	}
	for(const auto& n:nodes)
		for(uint i=0; i<n->nbArgs; i++){
			in>>tmp;
			if(tmp>=0)
				n->sockets[i]->connectToNode(nodes.at(tmp));
		}
	addNodes(nodes);
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
