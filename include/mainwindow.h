#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUndoStack>
#include <QClipboard>
#include <QMessageBox>

#include "include/ExportImageDialog.h"
#include <include/nodes/ConstNode.h>
#include <include/nodes/MathNode.h>
#include <include/nodes/PaletteNode.h>
#include <include/nodes/BitmapNode.h>
#include <include/nodes/ColorNode.h>
#include <include/nodes/ComplexNode.h>
#include <include/nodes/Node.h>
#include <include/nodes/IfNode.h>
#include <include/nodes/LogicNode.h>
#include <include/nodes/CompNode.h>
#include <include/nodes/RenderNode.h>
#include <include/commands.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);

private:
	Ui::MainWindow *ui;
	QUndoStack* undoStack;
	QList<Node*> textToNodes(const QByteArray& ba);
	QByteArray nodesToText(const QList<QGraphicsItem *> &nodes)const;
	Node* nodeMalloc(uint g, void *arg=nullptr);
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
	void select_all();
	void delete_selected();
	void drop(QDropEvent*event);

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
