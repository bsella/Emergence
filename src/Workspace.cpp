#include "lib/Workspace.h"
#include "lib/Palette.h"
#include "lib/PaletteGate.h"
Workspace::Workspace(QWidget *parent):QGraphicsView(parent),scene(new QGraphicsScene){
	setScene(scene);
}

void Workspace::setRA(RenderArea* ra){
	if (!ra) return ;
	renderArea=ra;
	scene->addItem(renderArea->xg);
	renderArea->yg->setY(100);
	scene->addItem(renderArea->yg);
	renderArea->start->setPos(100,50);
	scene->addItem(renderArea->start);
	connect(renderArea->xg,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	connect(renderArea->yg,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	connect(renderArea->start,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
}

void Workspace::addIFGate(){
	FuncGate * g= new IfGate;
	connect(g,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	scene->addItem(g);
}
void Workspace::addGTGate(){
	FuncGate* g=new GTGate;
	connect(g,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	scene->addItem(g);
}
void Workspace::addGEGate(){
	FuncGate* g=new GEGate;
	connect(g,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	scene->addItem(g);
}
void Workspace::addLTGate(){
	FuncGate* g=new LTGate;
	connect(g,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	scene->addItem(g);
}
void Workspace::addLEGate(){
	FuncGate* g=new LEGate;
	connect(g,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	scene->addItem(g);
}
void Workspace::addEQGate(){
	FuncGate* g=new EQGate;
	connect(g,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	scene->addItem(g);
}
void Workspace::addNEGate(){
	FuncGate* g=new NEGate;
	connect(g,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	scene->addItem(g);
}
void Workspace::addANDGate(){
	FuncGate* g=new ANDGate;
	connect(g,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	scene->addItem(g);
}
void Workspace::addORGate(){
	FuncGate* g=new ORGate;
	connect(g,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	scene->addItem(g);
}
void Workspace::addXORGate(){
	FuncGate* g=new XORGate;
	connect(g,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	scene->addItem(g);
}
void Workspace::addNANDGate(){
	FuncGate* g=new NANDGate;
	connect(g,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	scene->addItem(g);
}
void Workspace::addNORGate(){
	FuncGate* g=new NORGate;
	connect(g,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	scene->addItem(g);
}
void Workspace::addXNORGate(){
	FuncGate* g=new XNORGate;
	connect(g,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	scene->addItem(g);
}
void Workspace::addNOTGate(){
	FuncGate* g=new NOTGate;
	connect(g,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	scene->addItem(g);
}

void Workspace::addCColorGate(){
	QColor c =QColorDialog::getColor();
	if(c.isValid()){
		FuncGate* g=new ConstGate(c.rgba());
		connect(g,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
		scene->addItem(g);
	}
}

void Workspace::addCNumberGate(){
	bool ok;
	double d =QInputDialog::getDouble(this,"Choose Number","",0,-2147483647,2147483647,3,&ok);
	if(ok){
		FuncGate* g=new ConstGate(d);
		connect(g,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
		scene->addItem(g);
	}
}

void Workspace::addCBoolGate(){

}
void Workspace::addRenderGate(){
	scene->addItem(renderArea->start);
}
void Workspace::addXGate(){
	scene->addItem(renderArea->xg);
}
void Workspace::addYGate(){
	scene->addItem(renderArea->yg);
}
void Workspace::addPaletteGate(){
	///TODO : Implement dialog for palette
	Palette p;
	p.add(0xffff0000,0);
	p.add(0xff0000ff,.5);
	p.add(0xff00ff00,1);
	FuncGate* g= new PaletteGate(p);
	connect(g,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	scene->addItem(g);
}

Workspace::~Workspace(){}
