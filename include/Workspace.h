#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QColorDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDropEvent>
#include <QMimeData>
#include <QClipboard>
#include <include/nodes/Node.h>
#include <include/nodes/IfNode.h>
#include <include/nodes/LogicNode.h>
#include <include/nodes/CompNode.h>
#include <include/RenderArea.h>
#include <include/nodes/ConstNode.h>
#include <include/nodes/MathNode.h>
#include <include/nodes/PaletteNode.h>
#include <include/nodes/BitmapNode.h>
#include <include/nodes/ColorNode.h>
#include <include/nodes/ComplexNode.h>

#define MAGIC_NUMBER 0xa1b2affd
#define SAVE_VERSION 0x00000003

class Workspace : public QGraphicsView{
	Q_OBJECT
public:
	Workspace(QWidget *parent=0);
	~Workspace();
	void setRA(RenderArea* ra);
public slots:
	Node* addNode(uint g, const QPointF& pos, bool load=false);
	Node* addNode(uint g, bool load=false);
	void removeFromList(Node *g);
	void save()const;
	void load();
	void copy()const;
	void cut();
	void paste();
	void select_all();
	void delete_selected();
private:
	QGraphicsScene* scene;
	QList<Node*> Nodes;
	RenderArea* renderArea=nullptr;
	void clear();
	void dropEvent(QDropEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	QList<Node*> selectedNodes()const;
	QByteArray nodesToText(const QList<Node*>&nodes)const;
	void textToNodes(const QByteArray& ba);
};

#endif // WORKSPACE_H
