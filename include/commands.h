#ifndef COMMAND_H
#define COMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>

#include "include/nodes/Node.h"
#include "include/nodes/ConstNode.h"

class AddNodeCommand: public QUndoCommand{
public:
	AddNodeCommand(Node* node, QGraphicsScene* scene,
					QUndoCommand* parent=0);
	~AddNodeCommand();
	void undo()override;
	void redo()override;
private:
	Node* _node;
	QGraphicsScene* _scene;
};

class DeleteNodeCommand: public QUndoCommand{
public:
	DeleteNodeCommand(Node* node,QGraphicsScene* scene,
								QUndoCommand* parent=0);
	void undo()override;
	void redo()override;
private:
	Node* _node;
	QVector<Node*> iNodes;
	QList<QPair<Node*,uint>> oConnections;
	QGraphicsScene* _scene;
};

class ConnectNodeCommand: public QUndoCommand{
public:
	ConnectNodeCommand(Node::Socket* s, Node* in,
					   QUndoCommand* parent=0);
	void undo()override;
	void redo()override;
private:
	Node::Socket* _socket;
	Node* _iNode;
};

class DisconnectNodeCommand: public QUndoCommand{
public:
	DisconnectNodeCommand(Node::Socket *s,
						  QUndoCommand* parent=0);
	void undo()override;
	void redo()override;
private:
	Node::Socket* _socket;
	Node* _node;
};

class MoveNodeCommand: public QUndoCommand{
public:
	MoveNodeCommand(Node *node, QUndoCommand* parent=0);
	void undo()override;
	void redo()override;
private:
	Node* _node;
	QPointF _pos;
	QPointF _oldPos;
};

#endif // COMMAND_H
