#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QGraphicsView>
#include <QDropEvent>
#include <QMimeData>
#include <QUndoStack>
#include <QClipboard>
#include "nodes/Node.h"

class Workspace : public QGraphicsView{
	Q_OBJECT
public:
	Workspace(QWidget *parent=0);
	QUndoStack undoStack;
	void addNode(Node *n);
	void addNode(Node* n, const QPointF& pos);
	void addNodes(const QList<Node *> &n);
private:
	constexpr static double scaleFactor=1.05;
	void dropEvent(QDropEvent*);
	void dragMoveEvent(QDragMoveEvent*);
public slots:
	void paste();
	void select_all()const;
	void delete_selected();
	void copy()const;
	void cut();
	void moveNodes();
	void connectNode(Node::Socket* s, Node* n);
	void disconnectNode(Node::Socket* s);
protected:
	virtual void wheelEvent(QWheelEvent*);
	virtual void dragEnterEvent(QDragEnterEvent*);
};

#endif // WORKSPACE_H
