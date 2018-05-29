#include "include/data_t.h"

data_t::operator bool()const{
	switch (t) {
	case TypeEnum::DOUBLE: return d>=1;
	case TypeEnum::COLOR: return clr!=0;
	case TypeEnum::COMPLEX: return std::real(c)>0 && std::imag(c)>0;
	default:return b;
	}
}

data_t::operator double()const{
	switch (t) {
	case TypeEnum::BOOL:
		return b? 1.0:0.0;
	case TypeEnum::COLOR:
		return ((clr&0xff)*.0722+			//BLUE
				((clr&0xff00)>>8)*.7152+	//GREEN
				((clr&0xff0000)>>16)*.2126	//RED
				)/256.0;
	case TypeEnum::COMPLEX:
		return std::abs(c);
	default: return d;
	}
}

data_t::operator color()const{
	if(t==TypeEnum::BOOL) return b? 0xffffffff:0xff000000;
	if(t==TypeEnum::DOUBLE){
		if(d>=1)return 0xffffffff;
		if(d<=0)return 0xff000000;
		uint8_t c= d*256;
		return 0xff000000+c+(c<<8)+(c<<16);
	}
	if(t==TypeEnum::COMPLEX){
		return QColor::fromHsv(359*(std::arg(c)+M_PI)/(M_PI*2),
							   255,
							   std::abs(c)>1?255:std::abs(c)*255).rgb();
	}
	return clr;
}

data_t::operator cplx()const{
	if(t==TypeEnum::BOOL) return b? 1:0;
	if(t==TypeEnum::DOUBLE) return cplx(d,0);
	return c;
}

data_t& data_t::operator=(double dd){
	t=TypeEnum::DOUBLE;
	d=dd;
	return *this;
}
data_t& data_t::operator=(bool bb){
	t=TypeEnum::BOOL;
	b=bb;
	return *this;
}
data_t& data_t::operator=(color uu){
	t=TypeEnum::COLOR;
	clr=uu;
	return *this;
}
data_t& data_t::operator=(QColor uu){
	t=TypeEnum::COLOR;
	clr=uu.rgb();
	return *this;
}
data_t& data_t::operator=(cplx cc){
	t=TypeEnum::COMPLEX;
	c=cc;
	return *this;
}

data_t operator> (data_t d1, data_t d2){return double(d1)>double(d2);}
data_t operator< (data_t d1, data_t d2){return double(d1)<double(d2);}
data_t operator==(data_t d1, data_t d2){return double(d1)==double(d2);}
data_t operator!=(data_t d1, data_t d2){return double(d1)!=double(d2);}
data_t operator>=(data_t d1, data_t d2){return double(d1)>=double(d2);}
data_t operator<=(data_t d1, data_t d2){return double(d1)<=double(d2);}

data_t operator+ (data_t d1, data_t d2){
	if(d1.t==TypeEnum::COMPLEX||d2.t==TypeEnum::COMPLEX)
		return d1.operator cplx()+d2.operator cplx();
	return double(d1)+double(d2);
}
data_t operator- (data_t d1, data_t d2){
	if(d1.t==TypeEnum::COMPLEX||d2.t==TypeEnum::COMPLEX)
		return d1.operator cplx()-d2.operator cplx();
	return double(d1)-double(d2);
}
data_t operator* (data_t d1, data_t d2){
	if(d1.t==TypeEnum::COMPLEX||d2.t==TypeEnum::COMPLEX)
		return d1.operator cplx()*d2.operator cplx();
	return double(d1)*double(d2);
}
data_t operator/ (data_t d1, data_t d2){
	if(d1.t==TypeEnum::COMPLEX||d2.t==TypeEnum::COMPLEX)
		return d1.operator cplx()/d2.operator cplx();
	return double(d1)/double(d2);
}

data_t data_t::sin()const{
	if(t==TypeEnum::DOUBLE)return qSin(d);
	return std::sin(c);
}
data_t data_t::cos()const{
	if(t==TypeEnum::DOUBLE)return qCos(d);
	return std::cos(c);
}
data_t data_t::sqrt()const{
	if(t==TypeEnum::DOUBLE)return qSqrt(d);
	return std::sqrt(c);
}
