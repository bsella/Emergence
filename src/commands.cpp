#include "include/commands.h"

AddNodeCommand::AddNodeCommand(const QList<Node*>& nodes,
				QGraphicsScene* scene,
			   QUndoCommand* parent): QUndoCommand(parent){
	_scene=scene;
	_nodes=nodes;
}
AddNodeCommand::AddNodeCommand(Node* node, QGraphicsScene* scene,
				QUndoCommand* parent): QUndoCommand(parent){
	_scene=scene;
	_nodes.append(node);
}
void AddNodeCommand::undo(){
	for(const auto& n:_nodes)
		_scene->removeItem(n);
	_scene->update();
}
void AddNodeCommand::redo(){
	_scene->clearSelection();
	for(const auto& n:_nodes){
		if(!n) continue;
		_scene->addItem(n);
		n->setSelected(true);
		n->setZValue(0);
		for(const auto& i: n->collidingItems())
			if(n->zValue()<= i->zValue())
				n->setZValue(i->zValue()+1);
	}
	_scene->update();
}
AddNodeCommand::~AddNodeCommand(){
	qDeleteAll(_nodes);
}

DeleteNodeCommand::DeleteNodeCommand(QGraphicsScene *scene, QUndoCommand *parent):QUndoCommand(parent){
	_scene=scene;
	for(auto& n:scene->selectedItems()){
		_nodes.append(n);
		iNodes.append(((Node*)n)->iNodes);
		oConnections.append(((Node*)n)->oConnections);
	}
}
void DeleteNodeCommand::undo(){
	for(int i=0;i<_nodes.size();i++){
		_scene->addItem(_nodes[i]);
		for(int j=0; j<iNodes[i].size();j++)
			if(iNodes[i][j])
				((Node*)_nodes[i])->sockets[j]->connectToNode(iNodes[i][j]);
		for(int j=0; j<oConnections[i].size();j++)
			oConnections[i][j].first->sockets[oConnections[i][j].second]->connectToNode((Node*)_nodes[i]);
	}
	_scene->update();
}
void DeleteNodeCommand::redo(){
	for(auto& n:_nodes){
		for(auto& s:((Node*)n)->sockets)
			s->disconnectNode();
		for(auto& c:((Node*)n)->oConnections)
			c.first->sockets[c.second]->disconnectNode();
		_scene->removeItem(n);
	}
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
