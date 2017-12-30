#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QInputDialog>
#include <QColorDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "include/Gate.h"
#include "include/IfGate.h"
#include "include/LogicGate.h"
#include "include/CompGate.h"
#include "include/RenderArea.h"
#include "include/ConstGate.h"
#include "include/MathGate.h"

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
#define NOT_G		14
#define X_G			15
#define Y_G			16
#define RENDER_G	17
#define ADD_G		18
#define SUB_G		19
#define MUL_G		20
#define DIV_G		21
#define NEG_G		22
#define SQRT_G		23
#define ABS_G		24
#define LERP_G		25
#define CLAMP_G		26

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
