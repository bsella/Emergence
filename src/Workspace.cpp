#include "include/Workspace.h"

Workspace::Workspace(QWidget *parent):QGraphicsView(parent),scene(new QGraphicsScene){
	setScene(scene);
	setAcceptDrops(true);
	setDragMode(DragMode::RubberBandDrag);
}

void Workspace::setRA(RenderArea* ra){
	if (!ra) return;
	renderArea=ra;
	addFuncNode(X_G,{0,0});
	addFuncNode(Y_G,{0,100});
	addFuncNode(RENDER_G,{100,50});
}

void Workspace::addFuncNode(uint g, bool load){
	addFuncNode(g, scene->sceneRect().center(), load);
}

void Workspace::addFuncNode(uint g, const QPointF& pos, bool load){
	Node* node;
	switch(g){
	case DOUBLE_G:{
		if(load){
			node=new ConstNode(0.0);
			break;
		}
		bool ok;
		double d =QInputDialog::getDouble(this,"Choose Number","",0,-2147483647,2147483647,3,&ok);
		if(!ok) return;
		node=new ConstNode(d);
		break;
	}
	case COLOR_G:{
		if(load){
			node=new ConstNode(0xffffffff);
			break;
		}
		QColor c =QColorDialog::getColor(Qt::white,this);
		if(!c.isValid()) return;
		node=new ConstNode(c.rgba());
		break;
	}
	case PALETTE_G:{
		///TODO : Implement dialog for palette
		Palette p;
		p.add(0xffff0000,0);
		p.add(0xff0000ff,.5);
		p.add(0xff00ff00,1);
		node= new LUTNode(p);
		break;
	}
	case BITMAP_G:{
		if(load){
			node=new BitmapNode;
			break;
		}
		QString f= QFileDialog::getOpenFileName(this,"Choose Image",".","Images (*.bmp)");
		if(f.isNull())return;
		node = new BitmapNode(f);
		break;
	}
	case IF_G:		node=new IfNode;break;
	case GT_G:		node=new GTNode;break;
	case LT_G:		node=new LTNode;break;
	case EQ_G:		node=new EQNode;break;
	case NE_G:		node=new NENode;break;
	case OR_G:		node=new ORNode;break;
	case AND_G:		node=new ANDNode;break;
	case XOR_G:		node=new XORNode;break;
	case NOT_G:		node=new NOTNode;break;
	case X_G:
		if(!renderArea) return;
		node=renderArea->xg;
		break;
	case Y_G:
		if(!renderArea) return;
		node= renderArea->yg;
		break;
	case RENDER_G:
		if(!renderArea) return;
		node=renderArea->start;
		break;
	case RATIO_G:
		if(!renderArea) return;
		node=renderArea->ratio;
		break;
	case ADD_G:		node=new ADDNode;break;
	case SUB_G:		node=new SUBNode;break;
	case MUL_G:		node=new MULNode;break;
	case DIV_G:		node=new DIVNode;break;
	case NEG_G:		node=new NEGNode;break;
	case SQRT_G:	node=new SQRTNode;break;
	case ABS_G:		node=new ABSNode;break;
	case LERP_G:	node=new LERPNode;break;
	case CLAMP_G:	node=new CLAMPNode;break;
	case SIN_G:		node=new SINNode;break;
	case COS_G:		node=new COSNode;break;
	case MIN_G:		node=new MINNode;break;
	case MAX_G:		node=new MAXNode;break;
	case RGB_G:		node=new RGBNode;break;
	case HSV_G:		node=new HSVNode;break;
	case CPLX_G:	node=new ComplexNode;break;
	default:return;
	}
	connect(node,SIGNAL(notifyRA()),renderArea,SLOT(repaint()));
	connect(node,SIGNAL(removeFromWS(Node*)),this,SLOT(removeFromList(Node*)));
	connect(scene,SIGNAL(selectionChanged()),node,SLOT(updateSelection()));
	node->setPos(pos-node->boundingRect().center());
	Nodes.push_back(node);
	scene->addItem(node);
	node->setZValue(0);
	for(const auto& i: node->collidingItems())
		if(node->zValue()<= i->zValue())
			node->setZValue(i->zValue()+1);
}

void Workspace::removeFromList(Node *g){
	Nodes.remove(g);
}

void Workspace::clear(){
	while(!Nodes.empty())
		Nodes.back()->removeNode();
}

void Workspace::createFile()const{
	QString f= QFileDialog::getSaveFileName(parentWidget(),"Save as...",".","Node Files (*.emrg)");
	if(f.isNull()) return;
	if(!f.endsWith(".emrg"))
		f.append(".emrg");
	QFile file(f);
	file.open(QIODevice::WriteOnly);
	file.resize(0);
	QDataStream out(&file);

	out << MAGIC_NUMBER;
	out << SAVE_VERSION;

	QByteArray NodeType, NodePos;
	std::map<Node*,int> NodeID;
	int id=0;
	for(const auto& g : Nodes)
		NodeID[g]=id++;
	for(const auto& g : Nodes){
		//saving Node type
		NodeType.append(g->id);
		if(g->id==DOUBLE_G){		//Special case for double Node
			double d=((ConstNode*)g)->val;
			NodeType.append(reinterpret_cast<const char*>(&d), sizeof(d));
		}else if(g->id==COLOR_G){		//Special case for color Node
			uint color=((ConstNode*)g)->val;
			NodeType.append(reinterpret_cast<const char*>(&color), sizeof(color));
		}
		//saving Node position
		float fx= g->x(), fy= g->y();
		NodePos.append(reinterpret_cast<const char*>(&fx), sizeof(fx));
		NodePos.append(reinterpret_cast<const char*>(&fy), sizeof(fy));
	}

	out<<int(Nodes.size());
	out.writeRawData(NodeType.data(),NodeType.size());
	out<<NodePos;
	for(const auto& g : Nodes)
		for(unsigned i=0; i<g->nbArgs;i++)
			out << (g->iNodes[i]? NodeID.at(g->iNodes[i]): -1);
}

void Workspace::loadNodesFromFile(){
	QString f= QFileDialog::getOpenFileName(parentWidget(),"Open File",".","Node Files (*.emrg)");
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
	std::map<int,Node*> NodeID;
	for(int i=0;i<n;i++){
		uchar id; in>>id;
		addFuncNode(id,true);
		if(id==DOUBLE_G){
			char c[sizeof(double)];
			in.readRawData(c,sizeof(double));
			QByteArray dArray(c,sizeof(double));
			((ConstNode*)Nodes.back())->val=*reinterpret_cast<const double*>(dArray.data());
		}else if(id==COLOR_G){
			char c[sizeof(unsigned)];
			in.readRawData(c,sizeof(unsigned));
			QByteArray cArray(c,sizeof(unsigned));
			unsigned color =*reinterpret_cast<const unsigned*>(cArray.data());
			((ConstNode*)Nodes.back())->val= color;
			((ConstNode*)Nodes.back())->color=color;
		}
		NodeID[i]=Nodes.back();
	}
	in>>n;
	char c[n];
	in.readRawData(c,n);
	QByteArray floats(c,n);
	for(auto& g : Nodes){
		float fx,fy;
		fx = *reinterpret_cast<const float*>(floats.data());
		floats=floats.mid(4);
		fy = *reinterpret_cast<const float*>(floats.data());
		floats=floats.mid(4);
		g->setPos(fx,fy);
	}
	scene->setSceneRect(scene->itemsBoundingRect());
	for(auto& node: Nodes)
		for(unsigned i=0; i<node->nbArgs; i++){
			in>>n;
			if(n>=0)
				node->sockets[i]->connectToNode(NodeID[n]);
		}
}

Workspace::~Workspace(){
	clear();
	delete scene;
	delete renderArea;
}

void Workspace::dragEnterEvent(QDragEnterEvent *event){
	event->setAccepted(event->mimeData()->text()=="nodeTool");
	QGraphicsView::dragEnterEvent(event);
}

void Workspace::dropEvent(QDropEvent *event){
	addFuncNode(event->mimeData()->data("type").toInt(),
				mapToScene(event->pos()));
}

void Workspace::dragMoveEvent(QDragMoveEvent *){}
