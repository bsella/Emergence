#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QColorDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include<QDropEvent>
#include<QMimeData>
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
#define SAVE_VERSION 0x00000002

class Workspace : public QGraphicsView{
	Q_OBJECT
public:
	Workspace(QWidget *parent=0);
	~Workspace();
	void setRA(RenderArea* ra);
	QGraphicsScene* scene;
public slots:
	void addFuncNode(uint g, const QPointF& pos, bool load=false);
	void addFuncNode(uint g, bool load=false);
	void removeFromList(Node *g);
	void createFile()const;
	void loadNodesFromFile();
private:
	std::list<Node*> Nodes;
	RenderArea* renderArea=nullptr;
	void clear();
	void dropEvent(QDropEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
};

#endif // WORKSPACE_H
