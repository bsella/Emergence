#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QFileDialog>
#include <QMessageBox>
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

#define MAGIC_NUMBER 0xa1b2affd
#define SAVE_VERSION 0x00000002

class Workspace : public QGraphicsView{
	Q_OBJECT
public:
	Workspace(QWidget *parent=0);
	~Workspace();
	void setRA(RenderArea* ra);
public slots:
	void addFuncGate(uint g, bool load);
	void removeFromList(Gate *g);
	void createFile()const;
	void loadGatesFromFile();
private:
	std::list<Gate*> gates;
	QGraphicsScene* scene;
	RenderArea* renderArea=nullptr;
	void clear();
};

#endif // WORKSPACE_H
