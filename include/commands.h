#ifndef COMMAND_H
#define COMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>

#include "include/nodes/Node.h"

class AddNodeCommand: public QUndoCommand{
public:
	AddNodeCommand(const QList<Node*>& nodes,
	                QGraphicsScene* scene,
					QUndoCommand* parent=0);
	AddNodeCommand(Node* node, QGraphicsScene* scene,
					QUndoCommand* parent=0);
	~AddNodeCommand();
	void undo()override;
	void redo()override;
private:
	QList<Node*> _nodes;
	QGraphicsScene* _scene;
};

class DeleteNodeCommand: public QUndoCommand{
public:
	explicit DeleteNodeCommand(QGraphicsScene* scene,
								QUndoCommand* parent=0);
	void undo()override;
	void redo()override;
private:
	QList<QGraphicsItem*> _nodes;
	QList<QVector<Node*>> iNodes;
	QList<QList<QPair<Node*,uint>>> oConnections;
	QGraphicsScene* _scene;
};

class ConnectNodeCommand: public QUndoCommand{
public:
	ConnectNodeCommand(Node* n, Node* in, uint rank,
					   QUndoCommand* parent=0);
	void undo()override;
	void redo()override;
private:
	Node* _node;
	Node* _iNode;
	uint _rank;
};

class DisconnectNodeCommand: public QUndoCommand{
public:
	DisconnectNodeCommand(Node* n, Node* in, uint rank,
						  QUndoCommand* parent=0);
	void undo()override;
	void redo()override;
private:
	Node* _node;
	Node* _iNode;
	uint _rank;
};

class MoveNodeCommand: public QUndoCommand{
public:
	MoveNodeCommand(const QList<Node*>& nodes,
	                QGraphicsScene* scene,
	                const QPointF& oldPos,
	                QUndoCommand* parent=0);
	void undo()override;
	void redo()override;
private:
	QList<Node*> nodes;
	QGraphicsScene* _scene;
	QPointF _oldPos;
	QPointF newPos;
};

#endif // COMMAND_H
