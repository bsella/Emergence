#include "include/nodes/MathNode.h"

MathNode::MathNode(unsigned i, unsigned n, unsigned w, unsigned h):Node(i,w,h,QColor(180,255,180),n){}

ADDNode::ADDNode():MathNode(ADD_G,2){}
SUBNode::SUBNode():MathNode(SUB_G,2){}
MULNode::MULNode():MathNode(MUL_G,2){}
DIVNode::DIVNode():MathNode(DIV_G,2){}
NEGNode::NEGNode():MathNode(NEG_G,1){}
SQRTNode::SQRTNode():MathNode(SQRT_G,1){}
ABSNode::ABSNode():MathNode(ABS_G,1){}
LERPNode::LERPNode():MathNode(LERP_G,3,50,100){}
CLAMPNode::CLAMPNode():MathNode(CLAMP_G,3,50,100){}
SINNode::SINNode():MathNode(SIN_G,1){}
COSNode::COSNode():MathNode(COS_G,1){}
MINNode::MINNode():MathNode(MIN_G,2){}
MAXNode::MAXNode():MathNode(MAX_G,2){}

void ADDNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	drawIcon(painter,":/icons/add.png");
}

void SUBNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	drawIcon(painter,":/icons/subtract.png");
}

void MULNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	drawIcon(painter,":/icons/multiply.png");
}

void DIVNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	drawIcon(painter,":/icons/divide.png");
}

void NEGNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	drawIcon(painter,":/icons/subtract.png");
}

void SQRTNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	QImage icon=QImage(":/icons/sqrt.png");
	painter->drawImage(width/2-icon.width()/2+5,height/2-icon.height()/2,icon);
}
void ABSNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	painter->drawText(boundingRect().center()-QPointF(12,0),"abs");
}
void LERPNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.topLeft()+QPointF(8,rect.height()/4.0+4),"1");
	painter->drawText(rect.topLeft()+QPointF(width/2,2*rect.height()/4.0+4),"lerp");
	painter->drawText(rect.topLeft()+QPointF(8,3*rect.height()/4.0+4),"0");
}
void CLAMPNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	QRectF rect=boundingRect();
	painter->drawText(rect.topLeft()+QPointF(8,rect.height()/4.0+4),"1");
	painter->drawText(rect.topLeft()+QPointF(width/2-10,2*rect.height()/4.0+4),"clamp");
	painter->drawText(rect.topLeft()+QPointF(8,3*rect.height()/4.0+4),"0");
}
void SINNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	painter->drawText(boundingRect().center()-QPointF(12,0),"sin");
}
void COSNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	painter->drawText(boundingRect().center()-QPointF(12,0),"cos");
}
void MINNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	painter->drawText(boundingRect().center()-QPointF(12,0),"min");
}
void MAXNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	painter->drawText(boundingRect().center()-QPointF(12,0),"max");
}

data_t ADDNode::eval(){
	if(validVal) return val;
	val= iNodes[0]->eval()+iNodes[1]->eval();
	validVal=true;
	return val;
}
data_t SUBNode::eval(){
	if(validVal) return val;
	val= iNodes[0]->eval()-iNodes[1]->eval();
	validVal=true;
	return val;
}
data_t MULNode::eval(){
	if(validVal) return val;
	val= iNodes[0]->eval()*iNodes[1]->eval();
	validVal=true;
	return val;
}
data_t DIVNode::eval(){
	if(validVal) return val;
	val= iNodes[0]->eval()/iNodes[1]->eval();
	validVal=true;
	return val;
}
data_t NEGNode::eval(){
	if(validVal) return val;
	val= -iNodes[0]->eval();
	validVal=true;
	return val;
}
data_t SQRTNode::eval(){
	if(validVal) return val;
	val= iNodes[0]->eval().sqrt();
	validVal=true;
	return val;
}
data_t ABSNode::eval(){
	if(validVal) return val;
	val= qAbs((double)iNodes[0]->eval());
	validVal=true;
	return val;
}
data_t LERPNode::eval(){
	if(validVal) return val;
	double alpha=iNodes[1]->eval();
	val=(1.0-alpha)*double(iNodes[2]->eval())+alpha*double(iNodes[0]->eval());
	validVal=true;
	return val;
}
data_t CLAMPNode::eval(){
	if(validVal) return val;
	double min=iNodes[2]->eval(), max=iNodes[0]->eval();
	if(!(max-min)) return 0.0;
	val= (double(iNodes[1]->eval())-min)/(max-min);
	validVal=true;
	return val;
}
data_t SINNode::eval(){
	if(validVal) return val;
	val= iNodes[0]->eval().sin();
	validVal=true;
	return val;
}
data_t COSNode::eval(){
	if(validVal) return val;
	val= iNodes[0]->eval().cos();
	validVal=true;
	return val;
}
data_t MINNode::eval(){
	if(validVal) return val;
	val= qMin(iNodes[0]->eval(),iNodes[1]->eval());
	validVal=true;
	return val;
}
data_t MAXNode::eval(){
	if(validVal) return val;
	val= qMax(iNodes[0]->eval(),iNodes[1]->eval());
	validVal=true;
	return val;
}
