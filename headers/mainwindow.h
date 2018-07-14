#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUndoStack>
#include <QClipboard>
#include <QMessageBox>
#include <QFile>

#include <ExportImageDialog.h>
#include <nodes/ConstNode.h>
#include <nodes/MathNode.h>
#include <nodes/PaletteNode.h>
#include <nodes/BitmapNode.h>
#include <nodes/ColorNode.h>
#include <nodes/ComplexNode.h>
#include <nodes/Node.h>
#include <nodes/IfNode.h>
#include <nodes/LogicNode.h>
#include <nodes/CompNode.h>
#include <nodes/RenderNode.h>
#include <nodes/PixelNode.h>
#include <nodes/FunctionNode.h>
#include <commands.h>

#define MAGIC_NUMBER 0xa1b2affd
#define SAVE_VERSION 0x00000003

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
private:
	Ui::MainWindow *ui;
	QUndoStack* undoStack;
	QList<Node*> binToNodes(const QByteArray& ba);
	QByteArray nodesToBin(const QList<QGraphicsItem *> &nodes)const;
	Node* nodeMalloc(Node::Type g, void *arg=nullptr);
	QGraphicsScene* scene;
	void addNode(Node *n);
	void addNode(Node *n, const QPointF& pos);
	void addNodes(const QList<Node *> &n);

private slots:
	void save()const;
	void load();
	void copy()const;
	void cut();
	void paste();
	void select_all()const;
	void delete_selected();
	void drop(QDropEvent*event);
	void moveNodes();
	void connectNode(Node::Socket* s, Node* n);
	void disconnectNode(Node::Socket* s);
	void updateActions();

	void on_actionExit_triggered();
	void on_actionExport_triggered();
	void on_actionIf_triggered();
	void on_actionGreaterThan_triggered();
	void on_actionLessThan_triggered();
	void on_actionEqual_triggered();
	void on_actionNot_Equal_triggered();
	void on_actionAND_triggered();
	void on_actionOR_triggered();
	void on_actionXOR_triggered();
	void on_actionNOT_triggered();
	void on_actionDouble_triggered();
	void on_actionColor_triggered();
	void on_actionLUT_triggered();
	void on_actionX_triggered();
	void on_actionY_triggered();
	void on_actionRender_triggered();
	void on_actionADD_triggered();
	void on_actionSUB_triggered();
	void on_actionMUL_triggered();
	void on_actionDIV_triggered();
	void on_actionNEG_triggered();
	void on_actionSQRT_triggered();
	void on_actionABS_triggered();
	void on_actionLerp_triggered();
	void on_actionClamp_triggered();
	void on_actionBitmap_triggered();
	void on_actionSin_triggered();
	void on_actionCos_triggered();
	void on_actionMin_triggered();
	void on_actionMax_triggered();
	void on_actionRatio_triggered();
	void on_actionComplex_triggered();
	void on_actionHSV_triggered();
	void on_actionRGB_triggered();
};

#endif // MAINWINDOW_H
