#include "lib/Workspace.h"

#include "lib/Palette.h"
#include "lib/PaletteGate.h"
Workspace::Workspace(QWidget *parent):QGraphicsView(parent),scene(new QGraphicsScene){
	setScene(scene);
	Palette p;
	p.add(0xffff0000,0);
	p.add(0xff0000ff,.5);
	p.add(0xff00ff00,1);
	scene->addItem(new PaletteGate(p));
}

void Workspace::setRA(RenderArea* ra){
	renderArea=ra;
	if(renderArea){
		scene->addItem(renderArea->xg);
		renderArea->yg->setY(100);
		scene->addItem(renderArea->yg);
		renderArea->start->setPos(100,50);
		scene->addItem(renderArea->start);
	}
}

void Workspace::addIFGate(){
	scene->addItem(new IfGate);
}
void Workspace::addGTGate(){
	scene->addItem(new GTGate);
}
void Workspace::addGEGate(){
	scene->addItem(new GEGate);
}
void Workspace::addLTGate(){
	scene->addItem(new LTGate);
}
void Workspace::addLEGate(){
	scene->addItem(new LEGate);
}
void Workspace::addEQGate(){
	scene->addItem(new EQGate);
}
void Workspace::addNEGate(){
	scene->addItem(new NEGate);
}
void Workspace::addANDGate(){
	scene->addItem(new ANDGate);
}
void Workspace::addORGate(){
	scene->addItem(new ORGate);
}
void Workspace::addXORGate(){
	scene->addItem(new XORGate);
}
void Workspace::addNANDGate(){
	scene->addItem(new NANDGate);
}
void Workspace::addNORGate(){
	scene->addItem(new NORGate);
}
void Workspace::addXNORGate(){
	scene->addItem(new XNORGate);
}
void Workspace::addNOTGate(){
	scene->addItem(new NOTGate);
}

void Workspace::addCColorGate(){
	QColor c =QColorDialog::getColor();
	if(c.isValid())
		scene->addItem(new ConstGate(c.rgba()));
}

void Workspace::addCNumberGate(){
	bool ok;
	double d =QInputDialog::getDouble(this,"Choose Number","",0,-2147483647,2147483647,3,&ok);
	if(ok)
		scene->addItem(new ConstGate(d));
}

void Workspace::addCBoolGate(){

}

Workspace::~Workspace(){}
