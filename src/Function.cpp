#include "Function.h"
#include "nodes/FunctionNode.h"

Function::InputNode::InputNode(uint rank):Node(Node::INPUT_G,40,40,Qt::lightGray),_rank(rank){
	actionDelete->setEnabled(false);
}
void Function::InputNode::paint(QPainter *p, const QStyleOptionGraphicsItem *o, QWidget *w){
	Node::paint(p,o,w);
	QRectF rect= boundingRect();
	p->drawText(rect.topLeft()+QPointF(8,2*rect.height()/4.0+4),QString::number(_rank));
}
data_t Function::InputNode::kernel()const{
	return FunctionNode::current->iNodes[_rank]->eval();
}

Function::OutputNode::OutputNode():Node(Node::OUTPUT_G,50,50,Qt::lightGray,1,true){
	actionDelete->setEnabled(false);
}
void Function::OutputNode::paint(QPainter *p, const QStyleOptionGraphicsItem *o, QWidget *w){
	Node::paint(p,o,w);
	Node::drawIcon(p,":/icons/arrow.png");
}

Function::Function(int n, const QString& name):QListWidgetItem(name), nbArgs(n){
	scene= new Workspace;
	start= new OutputNode;
	scene->addItem(start);
	for(int i=0;i<nbArgs;i++){
		iNodes.append(new InputNode(i));
		scene->addItem(iNodes[i]);
	}
}
Function::Function(){
	scene= new Workspace;
}
Function::~Function(){
	for(int i=nbArgs-1;i>=0;i--)
		delete iNodes[i];
	delete start;
//	delete scene;
}

Function::OutputNode * Function::getOutputFromScene()const{
	for(const auto& n: scene->nodes())
		if(n->id==Node::OUTPUT_G)
			return (OutputNode*)n;
	return nullptr;
}
Function::InputNode * Function::getNthInputFromScene(int n)const{
	for(const auto& node: scene->nodes())
		if(node->id==Node::INPUT_G&& ((InputNode*)node)->_rank==n)
			return (InputNode*)node;
	return nullptr;
}

std::ostream& operator<<(std::ostream& out, const Function&f){
	out << f.text().toStdString()<<"\n";
	out << *(f.scene);
	out << f.nbArgs << '\n';
	return out;
}
