#include "Function.h"
#include "FunctionNode.h"

Function::FunctionInputNode::FunctionInputNode(uint rank):Node("fin",40,40,Qt::lightGray),_rank(rank){
	actionDelete->setEnabled(false);
}
void Function::FunctionInputNode::paint(QPainter *p, const QStyleOptionGraphicsItem *o, QWidget *w){
	Node::paint(p,o,w);
	QRectF rect= boundingRect();
	p->drawText(rect.topLeft()+QPointF(8,2*rect.height()/4.0+4),QString::number(_rank));
}
data_t Function::FunctionInputNode::kernel()const{
	return FunctionNode::current->iNodes[_rank]->eval();
}

Function::FunctionOutputNode::FunctionOutputNode():Node("fout",50,50,Qt::lightGray,1,true){
	actionDelete->setEnabled(false);
}
void Function::FunctionOutputNode::paint(QPainter *p, const QStyleOptionGraphicsItem *o, QWidget *w){
	Node::paint(p,o,w);
	Node::drawIcon(p,":/arrow.png");
}

Function::Function(int n, const QString& name):QListWidgetItem(name), nbArgs(n){
	scene= new Workspace;
	start= new FunctionOutputNode;
	scene->addItem(start);
	for(int i=0;i<nbArgs;i++){
		iNodes.append(new FunctionInputNode(i));
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

Function::FunctionOutputNode * Function::getOutputFromScene()const{
	for(const auto& n: scene->nodes())
		if(n->_type=="fout")
			return (FunctionOutputNode*)n;
	return nullptr;
}
Function::FunctionInputNode *Function::getNthInputFromScene(int n)const{
	for(const auto& node: scene->nodes())
		if(node->_type=="fin"&& ((FunctionInputNode*)node)->_rank==n)
			return (FunctionInputNode*)node;
	return nullptr;
}

std::ostream& operator<<(std::ostream& out, const Function&f){
	out << f.text().toStdString()<<"\n";
	out << *(f.scene);
	out << f.nbArgs << '\n';
	return out;
}
