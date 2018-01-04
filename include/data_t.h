#ifndef DATA_T_H
#define DATA_T_H

#include <complex>

enum class TypeEnum{
	BOOL=0x1,
	DOUBLE=0x2,
	COLOR=0x4,
	COMPLEX=0x8,
	ANY=0xf
};

typedef std::complex<double> cplx;

struct data_t{
	TypeEnum t;
	union{
		bool b;
		double d;
		unsigned int u;
		cplx c;
	};
	explicit data_t():t(TypeEnum::ANY){}
	data_t(double v):t(TypeEnum::DOUBLE), d(v){}
	data_t(bool v):t(TypeEnum::BOOL), b(v){}
	data_t(unsigned v):t(TypeEnum::COLOR), u(v){}
	data_t(cplx v):t(TypeEnum::COMPLEX), c(v){}
	operator bool(){
		if(t==TypeEnum::DOUBLE) return d>=1;
		if(t==TypeEnum::COLOR) return u!=0;
		if(t==TypeEnum::COMPLEX) return std::real(c)>0 && std::imag(c)>0;
		return b;
	}
	operator double(){
		if(t==TypeEnum::BOOL) return b? 1.0:0.0;
		if(t==TypeEnum::COLOR){
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
		if(t==TypeEnum::COMPLEX) return std::abs(c);
		return d;
	}
	operator unsigned(){
		if(t==TypeEnum::BOOL) return b? 0xffffffff:0xff000000;
		if(t==TypeEnum::DOUBLE){
			if(d>=1)return 0xffffffff;
			if(d<=0)return 0xff000000;
			unsigned char c= d*256;
			unsigned int i=0xff;
			i<<=8; i|=c;
			i<<=8; i|=c;
			i<<=8; i|=c;
			return i;
		}
		///TODO : convert complex to color
		if(t==TypeEnum::COMPLEX){
			return 0xff000000;
		}
		return u;
	}
	operator cplx(){
		if(t==TypeEnum::BOOL) return b? 1:0;
		if(t==TypeEnum::DOUBLE) return cplx(d,0);
		return c;
	}
	friend bool operator> (data_t d1, data_t d2){return double(d1)>double(d2);}
	friend bool operator< (data_t d1, data_t d2){return double(d1)<double(d2);}
	friend bool operator==(data_t d1, data_t d2){return double(d1)==double(d2);}
	friend bool operator!=(data_t d1, data_t d2){return double(d1)!=double(d2);}
	friend bool operator>=(data_t d1, data_t d2){return double(d1)>=double(d2);}
	friend bool operator<=(data_t d1, data_t d2){return double(d1)<=double(d2);}
	friend bool operator^ (data_t b1, data_t b2){return bool(b1)^bool(b2);}
	friend data_t operator+ (data_t d1, data_t d2){return double(d1)+double(d2);}
	friend data_t operator- (data_t d1, data_t d2){return double(d1)-double(d2);}
	friend data_t operator* (data_t d1, data_t d2){return double(d1)*double(d2);}
	friend data_t operator/ (data_t d1, data_t d2){return double(d1)/double(d2);}
	data_t operator- (){return -d;}
	data_t& operator=(double dd){
		t=TypeEnum::DOUBLE;
		d=dd;
		return *this;
	}
	data_t& operator=(bool bb){
		t=TypeEnum::BOOL;
		b=bb;
		return *this;
	}
	data_t& operator=(unsigned uu){
		t=TypeEnum::COLOR;
		u=uu;
		return *this;
	}
	data_t& operator=(cplx cc){
		t=TypeEnum::COMPLEX;
		c=cc;
		return *this;
	}
};

#endif // DATA_T_H
