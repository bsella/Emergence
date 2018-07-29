#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QDropEvent>
#include <QMimeData>
#include <QUndoStack>
#include <QClipboard>
#include "nodes/Node.h"

class Workspace : public QGraphicsScene{
	Q_OBJECT
public:
	Workspace(QWidget *parent=0);
	QUndoStack undoStack;
	constexpr static double scaleFactor=1.05;
	void addNode(Node*);
	void addNode(Node*, const QPointF&);
	void addNodes(const QList<Node *>&);
	void putXYandOutput();
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


#endif // WORKSPACE_H
