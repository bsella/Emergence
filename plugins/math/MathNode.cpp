#include "nodes/MathNode.h"

MathNode::MathNode(Type i, unsigned n, unsigned w, unsigned h):Node(i,w,h,QColor(180,255,180),n){}

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
POWNode::POWNode():MathNode(POW_G,2){}
LOGNode::LOGNode():MathNode(LOG_G,1){}

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
	drawIcon(painter,":/icons/neg.png");
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
void POWNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	painter->drawText(boundingRect().center()-QPointF(12,0),"pow");
}
void LOGNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Node::paint(painter,option,widget);
	painter->drawText(boundingRect().center()-QPointF(12,0),"log");
}
data_t ADDNode::kernel()const{
	return iNodes[0]->eval()+iNodes[1]->eval();
}
data_t SUBNode::kernel()const{
	return iNodes[0]->eval()-iNodes[1]->eval();
}
data_t MULNode::kernel()const{
	return iNodes[0]->eval()*iNodes[1]->eval();
}
data_t DIVNode::kernel()const{
	return iNodes[0]->eval()/iNodes[1]->eval();
}
data_t NEGNode::kernel()const{
	return -iNodes[0]->eval();
}
data_t SQRTNode::kernel()const{
	return iNodes[0]->eval().sqrt();
}
data_t ABSNode::kernel()const{
	return qAbs((double)iNodes[0]->eval());
}
data_t LERPNode::kernel()const{
	double alpha=iNodes[1]->eval();
	return (1.0-alpha)*double(iNodes[2]->eval())+alpha*double(iNodes[0]->eval());
}
data_t CLAMPNode::kernel()const{
	double min=iNodes[2]->eval(), max=iNodes[0]->eval();
	if(!(max-min)) return 0.0;
	return (double(iNodes[1]->eval())-min)/(max-min);
}
data_t SINNode::kernel()const{
	return iNodes[0]->eval().sin();
}
data_t COSNode::kernel()const{
	return iNodes[0]->eval().cos();
}
data_t MINNode::kernel()const{
	return qMin(iNodes[0]->eval(),iNodes[1]->eval());
}
data_t MAXNode::kernel()const{
	return qMax(iNodes[0]->eval(),iNodes[1]->eval());
}
data_t POWNode::kernel()const{
	return pow(iNodes[0]->eval(),iNodes[1]->eval());
}
data_t LOGNode::kernel()const{
	return iNodes[0]->eval().log();
}
