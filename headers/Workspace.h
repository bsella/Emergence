#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QGraphicsView>
#include <QDropEvent>
#include <QMimeData>
#include <QUndoStack>
#include <QClipboard>

#include <commands.h>

class Workspace : public QGraphicsView{
	Q_OBJECT
public:
	Workspace(QWidget *parent=0);
	QUndoStack undoStack;
	void addNode(Node::Type id);
	void addNode(Node::Type id, const QPointF& pos);
	void addNodes(const QList<Node *> &n);
private:
	constexpr static double scaleFactor=1.05;
	void dropEvent(QDropEvent*);
	void dragMoveEvent(QDragMoveEvent*);
	void wheelEvent(QWheelEvent*);
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
	virtual void dragEnterEvent(QDragEnterEvent*);
};

#endif // WORKSPACE_H
