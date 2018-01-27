#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QFileDialog>
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
#include "include/PaletteGate.h"
#include "include/BitmapGate.h"

#define BOOL_G		0
#define DOUBLE_G	1
#define COLOR_G		2
#define IF_G		3
#define PALETTE_G	4
#define GT_G		5
#define LT_G		6
#define EQ_G		7
#define NE_G		8
#define OR_G		9
#define AND_G		10
#define XOR_G		11
#define NOT_G		12
#define X_G			13
#define Y_G			14
#define RENDER_G	15
#define ADD_G		16
#define SUB_G		17
#define MUL_G		18
#define DIV_G		19
#define NEG_G		20
#define SQRT_G		21
#define ABS_G		22
#define LERP_G		23
#define CLAMP_G		24
#define BITMAP_G	25
#define SIN_G		26
#define COS_G		27
#define MIN_G		28
#define MAX_G		29

class Workspace : public QGraphicsView{
	Q_OBJECT
public:
	Workspace(QWidget *parent=0);
	void setRA(RenderArea* ra);
public slots:
	void addFuncGate(uint g);
	void addToList(Gate *g);
	void removeFromList(Gate *g);
private:
	std::list<Gate*> gates;
	QGraphicsScene* scene;
	RenderArea* renderArea=nullptr;
};

#endif // WORKSPACE_H
