#include "include/data_t.h"

data_t::data_t():t(TypeEnum::ANY){}
data_t::data_t(double v):t(TypeEnum::DOUBLE),d(v){}
data_t::data_t(bool v):t(TypeEnum::BOOL),b(v){}
data_t::data_t(uint v):t(TypeEnum::COLOR),u(v){}
data_t::data_t(cplx v):t(TypeEnum::COMPLEX),c(v){}

data_t::operator bool()const{
	switch (t) {
	case TypeEnum::DOUBLE: return d>=1;
	case TypeEnum::COLOR: return u!=0xff000000;
	case TypeEnum::COMPLEX: return std::real(c)>0 && std::imag(c)>0;
	default: return *this;
	}
}

data_t::operator double()const{
	switch(t){
	case TypeEnum::BOOL: return b? 1.0:0.0;
	case TypeEnum::COLOR:{
		uint temp=u;
		double ret=0;
		uint8_t color= temp;
		ret+=color*.0722;	///BLUE
		temp>>=8;
		color=temp;
		ret+=color*.7152;	///GREEN
		temp>>=8;
		color=temp;
		ret+=color*.2126;	///RED
		return ret/256.0;
	}
	case TypeEnum::COMPLEX: return std::abs(c);
	default: return d;
	}
}

data_t::operator unsigned()const{
	switch (t) {
	case TypeEnum::BOOL: return b? 0xffffffff:0xff000000;
	case TypeEnum::DOUBLE:{
		if(d>=1)return 0xffffffff;
		if(d<=0)return 0xff000000;
		unsigned char c= d*256;
		unsigned int i=0xff00;
		i|=c;
		i<<=8; i|=c;
		i<<=8; i|=c;
		return i;
	}
	///TODO : convert complex to color
	case TypeEnum::COMPLEX: return 0xff000000;
	default: return u;
	}
}

data_t::operator cplx()const{
	if(t==TypeEnum::BOOL) return b? 1:0;
	if(t==TypeEnum::DOUBLE) return cplx(d,0);
	return c;
}

bool operator>(data_t d1, data_t d2){
	return double(d1)>double(d2);
}
bool operator<(data_t d1, data_t d2){
	return double(d1)<double(d2);
}
bool operator==(data_t d1, data_t d2){
	return double(d1)==double(d2);
}
bool operator!=(data_t d1, data_t d2){
	return double(d1)!=double(d2);
}
bool operator>=(data_t d1, data_t d2){
	return double(d1)>=double(d2);
}
bool operator<=(data_t d1, data_t d2){
	return double(d1)<=double(d2);
}
bool operator^(data_t d1, data_t d2){
	return bool(d1)^bool(d2);
}

data_t operator+(data_t d1, data_t d2){
//	if(d1.t==TypeEnum::COLOR || d2.t==TypeEnum::COLOR){
//		d1=uint(d1); d2=uint(d2);

//		uint ret=0xff00;
//		uint8_t b1= d1.u, b2=d2.u;	///GET BLUE
//		d1.u>>=8; d2.u>>=8;
//		uint8_t g1= d1.u, g2=d2.u;	///GET GREEN
//		d1.u>>=8; d2.u>>=8;
//		uint8_t r1= d1.u, r2=d2.u;	///GET RED

//		if(r1+r2>=0xff) ret|=0xff;	///SET RED
//		else ret|=(r1+r2);
//		ret<<=8;
//		if(g1+g2>=0xff) ret|=0xff;	///SET GREEN
//		else ret|=(g1+g2);
//		ret<<=8;
//		if(b1+b2>=0xff) ret|=0xff;	///SET BLUE
//		else ret|=(b1+b2);
//		return ret;
//	}
	return double(d1)+double(d2);
}

data_t operator-(data_t d1, data_t d2){
//	if(d1.t==TypeEnum::COLOR || d2.t==TypeEnum::COLOR){
//		d1=uint(d1); d2=uint(d2);
//		uint ret=0xff00;
//		uint8_t b1= d1.u, b2=d2.u;	///GET BLUE
//		d1.u>>=8; d2.u>>=8;
//		uint8_t g1= d1.u, g2=d2.u;	///GET GREEN
//		d1.u>>=8; d2.u>>=8;
//		uint8_t r1= d1.u, r2=d2.u;	///GET RED

//		if(r1-r2>0) ret|=(r1-r2);	///SET RED
//		ret<<=8;
//		if(g1-g2>0) ret|=(g1-g2);	///SET GREEN
//		ret<<=8;
//		if(b1-b2>0) ret|=(b1-b2);	///SET BLUE
//		return ret;
//	}
	return double(d1)-double(d2);
}

data_t operator*(data_t d1, data_t d2){
	///TODO : multiply colors by numbers
	return double(d1)*double(d2);
}

data_t operator/(data_t d1, data_t d2){
	return double(d1)/double(d2);
}

data_t data_t::operator-()const{
	if(t==TypeEnum::COLOR){
		uint temp=u;

		uint8_t b= temp;	///GET BLUE
		temp>>=8;
		uint8_t g= temp;	///GET GREEN
		temp>>=8;
		uint8_t r= temp;	///GET RED

		uint ret=0xff00;
		ret|=(0xff-r);	///SET RED
		ret<<=8;
		ret|=(0xff-g);	///SET GREEN
		ret<<=8;
		ret|=(0xff-b);	///SET BLUE
		return ret;
	}
	return -d;
}

data_t& data_t::operator =(double dd){
	t=TypeEnum::DOUBLE;
	d=dd;
	return *this;
}
data_t& data_t::operator=(bool bb){
	t=TypeEnum::BOOL;
	b=bb;
	return *this;
}
data_t& data_t::operator=(unsigned uu){
	t=TypeEnum::COLOR;
	u=uu;
	return *this;
}
data_t& data_t::operator=(cplx cc){
	t=TypeEnum::COMPLEX;
	c=cc;
	return *this;
}
