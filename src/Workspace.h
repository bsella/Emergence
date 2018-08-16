#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QDropEvent>
#include <QMimeData>
#include <QUndoStack>
#include <QClipboard>
#include "Node.h"

class Workspace : public QGraphicsScene{
	Q_OBJECT
public:
	Workspace(QWidget *parent=0);
	QUndoStack undoStack;
	constexpr static double scaleFactor=1.05;
	void addNode(Node*);
	void addNode(Node*, const QPointF&);
	void addNodes(const QList<Node *>&);
	friend std::ostream& operator<<(std::ostream& out, const Workspace& w);
	friend std::istream& operator>>(std::istream& in, Workspace& w);
	int count()const;
	Node* nodeAt(int)const;
	int nodeIndex(Node*)const;
	QList<Node*> nodes()const;
private:
	void dragEnterEvent(QGraphicsSceneDragDropEvent *);
	void dragMoveEvent(QGraphicsSceneDragDropEvent*);
	void dropEvent(QGraphicsSceneDragDropEvent*);
public slots:
	void paste();
	void select_all()const;
	void delete_selected();
	void copy()const;
	void cut();
	void moveNodes();
	void connectNode(Node::Socket*, Node*);
	void disconnectNode(Node::Socket*);
};

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

#endif // WORKSPACE_H
