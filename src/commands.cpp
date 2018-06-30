#include "include/commands.h"

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
