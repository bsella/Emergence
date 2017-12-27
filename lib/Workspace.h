#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QInputDialog>
#include <QColorDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "lib/Gate.h"
#include "lib/IfGate.h"
#include "lib/LogicGate.h"
#include "lib/CompGate.h"
#include "lib/RenderArea.h"
#include "lib/ConstGate.h"
#include "lib/MathGate.h"

#define BOOL_G		0
#define DOUBLE_G	1
#define COLOR_G		2
#define IF_G		3
#define PALETTE_G	4
#define GT_G		5
#define GE_G		6
#define LT_G		7
#define LE_G		8
#define EQ_G		9
#define NE_G		10
#define OR_G		11
#define AND_G		12
#define XOR_G		13
#define NAND_G		14
#define NOR_G		15
#define XNOR_G		16
#define NOT_G		17
#define X_G			18
#define Y_G			19
#define RENDER_G	20
#define ADD_G		21
#define SUB_G		22
#define MUL_G		23
#define DIV_G		24
#define NEG_G		25
#define SQRT_G		26

class Workspace : public QGraphicsView{
	Q_OBJECT
public:
	Workspace(QWidget *parent=0);
	~Workspace();
	void setRA(RenderArea* ra);
public slots:
	void addFuncGate(uint g);
private:
	QGraphicsScene* scene;
	RenderArea* renderArea=nullptr;
};

#endif // WORKSPACE_H
