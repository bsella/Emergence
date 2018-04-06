#include "include/Workspace.h"

Workspace::Workspace(QWidget *parent):QGraphicsView(parent),scene(new QGraphicsScene){
	setScene(scene);
}

void Workspace::setRA(RenderArea* ra){
	if (!ra) return ;
	renderArea=ra;
	addFuncGate(RENDER_G,false);
	addFuncGate(X_G,false);
	addFuncGate(Y_G,false);
	renderArea->xg->setPos(0,0);
	renderArea->yg->setPos(0,100);
	renderArea->start->setPos(100,50);
}

void Workspace::addFuncGate(uint g, bool load){
	Gate* gate;
	switch(g){
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
		QColor c =QColorDialog::getColor(Qt::white,this);
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
	case RATIO_G:
		if(!renderArea) return;
		gate=renderArea->ratio;
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
	case RGB_G:		gate=new RGBGate;break;
	case HSV_G:		gate=new HSVGate;break;
	default:return;
	}
	connect(gate,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	connect(gate,SIGNAL(removeFromWS(Gate*)),this,SLOT(removeFromList(Gate*)));
	gate->setPos(scene->sceneRect().center());
	gates.push_back(gate);
	scene->addItem(gate);
	gate->setZValue(0);
	for(const auto& i: gate->collidingItems())
		if(gate->zValue()<= i->zValue())
			gate->setZValue(i->zValue()+1);
}

#include <iostream>
void Workspace::removeFromList(Gate *g){
	gates.remove(g);
}

void Workspace::clear(){
	while(!gates.empty())
		gates.back()->removeGate();
}

void Workspace::createFile()const{
	QString f= QFileDialog::getSaveFileName(parentWidget(),"Save as...",".","Gate Files (*.gate)");
	if(f.isNull()) return;
	if(!f.endsWith(".gate"))
		f.append(".gate");
	QFile file(f);
	file.open(QIODevice::WriteOnly);
	file.resize(0);
	QDataStream out(&file);

	out << MAGIC_NUMBER;
	out << SAVE_VERSION;

	QByteArray gateType, gatePos;
	std::map<Gate*,int> gateID;
	int id=0;
	for(const auto& g : gates)
		gateID[g]=id++;
	for(const auto& g : gates){
		//saving gate type
		gateType.append(g->id);
		if(g->id==DOUBLE_G){		//Special case for double gate
			double d=((ConstGate*)g)->val;
			gateType.append(reinterpret_cast<const char*>(&d), sizeof(d));
		}else if(g->id==COLOR_G){		//Special case for color gate
			uint color=((ConstGate*)g)->val;
			gateType.append(reinterpret_cast<const char*>(&color), sizeof(color));
		}
		//saving gate position
		float fx= g->x(), fy= g->y();
		gatePos.append(reinterpret_cast<const char*>(&fx), sizeof(fx));
		gatePos.append(reinterpret_cast<const char*>(&fy), sizeof(fy));
	}

	out<<int(gates.size());
	out.writeRawData(gateType.data(),gateType.size());
	out<<gatePos;
	for(const auto& g : gates)
		for(unsigned i=0; i<g->nbArgs;i++)
			out << (g->iGates[i]? gateID.at(g->iGates[i]): -1);
}

void Workspace::loadGatesFromFile(){
	QString f= QFileDialog::getOpenFileName(parentWidget(),"Open File",".","Gate Files (*.gate)");
	if(f.isNull()) return;
	QFile file(f);
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);
	uint magic; in>>magic;
	if(magic!=MAGIC_NUMBER){
		QMessageBox::warning(0,"Wrong format","Bad File Format");
		return;
	}
	uint version; in>>version;
	if(version<SAVE_VERSION){
		QMessageBox::warning(0,"Wrong version","Sorry, this save file is too old.");
		return;
	}
	clear();
	int n; in>>n;
	std::map<int,Gate*> gateID;
	for(int i=0;i<n;i++){
		uchar id; in>>id;
		addFuncGate(id,true);
		if(id==DOUBLE_G){
			char c[sizeof(double)];
			in.readRawData(c,sizeof(double));
			QByteArray dArray(c,sizeof(double));
			((ConstGate*)gates.back())->val=*reinterpret_cast<const double*>(dArray.data());
		}else if(id==COLOR_G){
			char c[sizeof(unsigned)];
			in.readRawData(c,sizeof(unsigned));
			QByteArray cArray(c,sizeof(unsigned));
			unsigned color =*reinterpret_cast<const unsigned*>(cArray.data());
			((ConstGate*)gates.back())->val= color;
			((ConstGate*)gates.back())->color=color;
		}
		gateID[i]=gates.back();
	}
	in>>n;
	char c[n];
	in.readRawData(c,n);
	QByteArray floats(c,n);
	for(auto& g : gates){
		float fx,fy;
		fx = *reinterpret_cast<const float*>(floats.data());
		floats=floats.mid(4);
		fy = *reinterpret_cast<const float*>(floats.data());
		floats=floats.mid(4);
		g->setPos(fx,fy);
	}
	scene->setSceneRect(scene->itemsBoundingRect());
	for(auto& g: gates)
		for(unsigned i=0; i<g->nbArgs; i++){
			in>>n;
			if(n>=0)
				g->connectGate(gateID[n],i);
		}
}

Workspace::~Workspace(){
	clear();
	delete scene;
	delete renderArea;
}
