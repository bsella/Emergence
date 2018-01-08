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
	connect(renderArea->xg,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	connect(renderArea->yg,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	connect(renderArea->start,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
}

void Workspace::addFuncGate(uint g){
	Gate* gate;
	switch(g){
	case BOOL_G:return;
	case DOUBLE_G:{
		bool ok;
		double d =QInputDialog::getDouble(this,"Choose Number","",0,-2147483647,2147483647,3,&ok);
		if(!ok) return;
		gate=new ConstGate(d);
		break;
	}
	case COLOR_G:{
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
		gate= new PaletteGate(p);
		break;
	}
	case BITMAP_G:{
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
	case X_G:		gate=new PixelXGate;break;
	case Y_G:		gate=new PixelYGate;break;
	case RENDER_G:	gate=new RenderGate;break;
	case ADD_G:		gate=new ADDGate;break;
	case SUB_G:		gate=new SUBGate;break;
	case MUL_G:		gate=new MULGate;break;
	case DIV_G:		gate=new DIVGate;break;
	case NEG_G:		gate=new NEGGate;break;
	case SQRT_G:	gate=new SQRTGate;break;
	case ABS_G:		gate=new ABSGate;break;
	case LERP_G:	gate=new LERPGate;break;
	case CLAMP_G:	gate=new CLAMPGate;break;
	default:return;
	}
	connect(gate,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	scene->addItem(gate);
}

Workspace::~Workspace(){}
