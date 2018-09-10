#ifndef GRADIENT_H
#define GRADIENT_H

#include <ostream>

class Gradient{
private:
	struct color{
		color(Gradient* p,unsigned c, double a);
		color(color*);
		Gradient* gr;
		struct color* next=nullptr;
		struct color* prev=nullptr;
		const unsigned clr;
		double alpha;
		void updateAlpha(double newAlpha);
	};
	void remove(color* c);
	static unsigned average(color c1, color c2, double i);
	struct color*first=nullptr;
	struct color*last=nullptr;
	friend class LutCursor;
	friend class LutView;
	friend std::ostream& operator<<(std::ostream&,const Gradient&);
public:
	Gradient();
	Gradient(const Gradient&);
	~Gradient();
	color* add(unsigned color, double alpha);
	unsigned operator[](double alpha)const;
	bool empty()const;
};

#endif
