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

class Workspace : public QGraphicsView{
	Q_OBJECT
public:
	Workspace(QWidget *parent=0);
	~Workspace();
	void setRA(RenderArea* ra);
public slots:
	void addIFGate();
	void addGTGate();
	void addGEGate();
	void addLTGate();
	void addLEGate();
	void addEQGate();
	void addNEGate();
	void addANDGate();
	void addORGate();
	void addXORGate();
	void addNANDGate();
	void addNORGate();
	void addXNORGate();
	void addNOTGate();
	void addCColorGate();
	void addCBoolGate();
	void addCNumberGate();
	void addPaletteGate();
	void addRenderGate();
	void addXGate();
	void addYGate();
private:
	QGraphicsScene* scene;
	RenderArea* renderArea=nullptr;
};

#endif // WORKSPACE_H
