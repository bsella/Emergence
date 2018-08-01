#ifndef DATA_T_H
#define DATA_T_H

#include <complex>
#include <QColor>
#include <QtMath>

enum class TypeEnum{
	BOOL=0x1,
	DOUBLE=0x2,
	COLOR=0x4,
	COMPLEX=0x8,
	ANY=0xf
};

typedef std::complex<double> cplx;

struct data_t{
	typedef uint32_t color;
	TypeEnum t;
	union{
		bool b;
		double d;
		color clr;
		cplx c;
	};
	explicit data_t():t(TypeEnum::ANY){}
	data_t(double v):t(TypeEnum::DOUBLE), d(v){}
	data_t(bool v):t(TypeEnum::BOOL), b(v){}
	data_t(unsigned v):t(TypeEnum::COLOR), clr(v){}
	data_t(cplx v):t(TypeEnum::COMPLEX), c(v){}
	operator bool()const;
	operator double()const;
	operator color()const;
	operator cplx()const;
	data_t& operator=(double dd);
	data_t& operator=(bool bb);
	data_t& operator=(color uu);
	data_t& operator=(QColor uu);
	data_t& operator=(cplx cc);
	data_t operator-()const;
	data_t sin()const;
	data_t cos()const;
	data_t sqrt()const;
	data_t log()const;
	friend data_t pow(data_t d1, data_t d2);
	friend data_t operator> (data_t d1, data_t d2);
	friend data_t operator< (data_t d1, data_t d2);
	friend data_t operator==(data_t d1, data_t d2);
	friend data_t operator!=(data_t d1, data_t d2);
	friend data_t operator>=(data_t d1, data_t d2);
	friend data_t operator<=(data_t d1, data_t d2);
	friend data_t operator+ (data_t d1, data_t d2);
	friend data_t operator- (data_t d1, data_t d2);
	friend data_t operator* (data_t d1, data_t d2);
	friend data_t operator/ (data_t d1, data_t d2);
};

#endif // DATA_T_H
