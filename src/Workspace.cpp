#include "include/Workspace.h"

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
	gates.push_back(renderArea->start);
	gates.push_back(renderArea->xg);
	gates.push_back(renderArea->yg);
	connect(renderArea->xg,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	connect(renderArea->yg,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	connect(renderArea->start,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	connect(renderArea->xg,SIGNAL(addToWS(Gate*)),this,SLOT(addToList(Gate*)));
	connect(renderArea->xg,SIGNAL(removeFromWS(Gate*)),this,SLOT(removeFromList(Gate*)));
	connect(renderArea->yg,SIGNAL(addToWS(Gate*)),this,SLOT(addToList(Gate*)));
	connect(renderArea->yg,SIGNAL(removeFromWS(Gate*)),this,SLOT(removeFromList(Gate*)));
	connect(renderArea->start,SIGNAL(addToWS(Gate*)),this,SLOT(addToList(Gate*)));
	connect(renderArea->start,SIGNAL(removeFromWS(Gate*)),this,SLOT(removeFromList(Gate*)));
}

void Workspace::addFuncGate(uint g, bool load){
	Gate* gate;
	switch(g){
	case BOOL_G:return;
	case DOUBLE_G:{
		if(load){
			gate=new ConstGate(0.0);
			break;
		}
		bool ok;
		double d =QInputDialog::getDouble(this,"Choose Number","",0,-2147483647,2147483647,3,&ok);
		if(!ok) return;
		gate=new ConstGate(d);
		break;
	}
	case COLOR_G:{
		if(load){
			gate=new ConstGate(0xffffffff);
			break;
		}
		QColor c =QColorDialog::getColor();
		if(!c.isValid()) return;
		gate=new ConstGate(c.rgba());
		break;
	}
	case PALETTE_G:{
		///TODO : Implement dialog for palette
		Palette p;
		p.add(0xffff0000,0);
		p.add(0xff0000ff,.5);
		p.add(0xff00ff00,1);
		gate= new LUTGate(p);
		break;
	}
	case BITMAP_G:{
		if(load){
			gate=new BitmapGate;
			break;
		}
		QString f= QFileDialog::getOpenFileName(this,"Choose Image",".","Images (*.bmp)");
		if(f.isNull())return;
		gate = new BitmapGate(f);
		break;
	}
	case IF_G:		gate=new IfGate;break;
	case GT_G:		gate=new GTGate;break;
	case LT_G:		gate=new LTGate;break;
	case EQ_G:		gate=new EQGate;break;
	case NE_G:		gate=new NEGate;break;
	case OR_G:		gate=new ORGate;break;
	case AND_G:		gate=new ANDGate;break;
	case XOR_G:		gate=new XORGate;break;
	case NOT_G:		gate=new NOTGate;break;
	case X_G:
		if(!renderArea) return;
		gate=renderArea->xg;
		break;
	case Y_G:
		if(!renderArea) return;
		gate= renderArea->yg;
		break;
	case RENDER_G:
		if(!renderArea) return;
		gate=renderArea->start;
		break;
	case ADD_G:		gate=new ADDGate;break;
	case SUB_G:		gate=new SUBGate;break;
	case MUL_G:		gate=new MULGate;break;
	case DIV_G:		gate=new DIVGate;break;
	case NEG_G:		gate=new NEGGate;break;
	case SQRT_G:	gate=new SQRTGate;break;
	case ABS_G:		gate=new ABSGate;break;
	case LERP_G:	gate=new LERPGate;break;
	case CLAMP_G:	gate=new CLAMPGate;break;
	case SIN_G:		gate=new SINGate;break;
	case COS_G:		gate=new COSGate;break;
	case MIN_G:		gate=new MINGate;break;
	case MAX_G:		gate=new MAXGate;break;
	default:return;
	}
	connect(gate,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	connect(gate,SIGNAL(addToWS(Gate*)),this,SLOT(addToList(Gate*)));
	connect(gate,SIGNAL(removeFromWS(Gate*)),this,SLOT(removeFromList(Gate*)));
	gate->setPos(scene->sceneRect().center());
	gates.push_back(gate);
	scene->addItem(gate);
	gate->setZValue(0);
	for(const auto& i: gate->collidingItems())
		if(gate->zValue()<= i->zValue())
			gate->setZValue(i->zValue()+1);
}

void Workspace::removeFromList(Gate *g){
	gates.remove(g);
}

void Workspace::addToList(Gate *g){
	gates.push_back(g);
}

void Workspace::createFile()const{
	QString f= QFileDialog::getSaveFileName(0,"Save as...",".","Gate Files (*.gate)");
	if(f.isNull()) return;
	if(!f.endsWith(".gate"))
		f.append(".gate");
	QFile file(f);
	file.open(QIODevice::WriteOnly);
	file.resize(0);
	QDataStream out(&file);

	out << MAGIC_NUMBER;
	out << SAVE_VERSION;

	for(const auto& g : gates)
		makeBinary(*g,out);
}

void Workspace::clearGate(Gate *g){
	for(uint i=0; i<g->nbArgs;i++)
		if(g->iGates[i]) clearGate(g->iGates[i]);
	if(g) g->removeGate();
}

void Workspace::clearAll(){
	for(auto& g: gates){
		clearGate(g);
	}
	gates.clear();
}

#include <iostream>
void Workspace::loadGatesFromFile(){
	QString f= QFileDialog::getOpenFileName(0,"Open File",".","Gate Files (*.gate)");
	if(f.isNull()) return;
	QFile file(f);
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);
	uint magic; in>>magic;
	if(magic!=MAGIC_NUMBER){
		QMessageBox::warning(0,"Wrong format","Wrong File Format");
		return;
	}
	uint version; in>>version;
	clearAll();
	while(!in.atEnd())
		makeGate(in,-1,nullptr);
	scene->setSceneRect(scene->itemsBoundingRect());
}


void Workspace::makeGate(QDataStream& in, int argument, Gate* toGate){
	uint size;
	unsigned char id,n;
	in.setFloatingPointPrecision(QDataStream::SinglePrecision);
	float x,y;
	in>>size;
	if(size){
		in>>id;
		in>>x; in>>y;
		in>>n;
		addFuncGate(id,true);
		Gate* g = gates.back();
		g->setPos(x,y);
		if(argument!=-1)
			toGate->connectGate(g,argument);
		for(int i=0; i<n;i++)
			makeGate(in,i,g);
	}
}

static void ftoc(float *f, char* c){
	memcpy(c,f,4);
	char a=c[0],a2=c[1];
	c[0]=c[3];
	c[1]=c[2];
	c[2]=a2;
	c[3]=a;
}

void Workspace::makeBinary(const Gate& g, QDataStream& out) const{
	out.setFloatingPointPrecision(QDataStream::SinglePrecision);
	QByteArray ret;
	ret.append(g.id);		// id
	char s[4];
	float f=g.x();
	ftoc(&f,s);
	ret.append(s,4);
	f=g.y();
	ftoc(&f,s);
	ret.append(s,4);
	unsigned n= g.nbArgs;
	ret.append(uchar(n));		//char[4]: nbArgs
	out <<ret;
	for(unsigned i =0; i<n; i++){
		if(!g.iGates[i])
			out<<0x0;
		else
			makeBinary(*g.iGates[i],out);
	}
}
