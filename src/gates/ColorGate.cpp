#include <include/gates/ColorGate.h>

ColorGate::ColorGate(unsigned i):Gate(i,50,100,Qt::white,3){}

RGBGate::RGBGate():ColorGate(RGB_G){}
HSVGate::HSVGate():ColorGate(HSV_G){}

void RGBGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter, option, widget);
	painter->fillRect(QRect(socketSize+2,height/4-5,width-4,10),Qt::red);
	painter->fillRect(QRect(socketSize+2,2*height/4-5,width-4,10),Qt::green);
	painter->fillRect(QRect(socketSize+2,3*height/4-5,width-4,10),Qt::blue);
}

void HSVGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Gate::paint(painter, option, widget);
	painter->drawText(width/4,height/4+4,"H");
	painter->drawText(width/4,2*height/4+4,"S");
	painter->drawText(width/4,3*height/4+4,"V");
}

data_t RGBGate::eval(){
	if(validVal) return val;
	int r=double(iGates[0]->eval())*255,
		g=double(iGates[1]->eval())*255,
		b=double(iGates[2]->eval())*255;
	r=qMax(r,0); r= qMin(r,255);
	g=qMax(g,0); g= qMin(g,255);
	b=qMax(b,0); b= qMin(b,255);
	val = QColor(r,g,b);
	validVal=true;
	return val;
}

data_t HSVGate::eval(){
	if(validVal) return val;
	int h=double(iGates[0]->eval())*360,
		s=double(iGates[1]->eval())*255,
		v=double(iGates[2]->eval())*255;
	h=qMax(h,0); h= qMin(h,359);
	s=qMax(s,0); s= qMin(s,255);
	v=qMax(v,0); v= qMin(v,255);
	val = QColor::fromHsv(h,s,v);
	validVal=true;
	return val;
}
