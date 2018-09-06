#ifndef PALETTE_H
#define PALETTE_H
#include <list>

class Palette{
public:
//private:
	struct color{
		color(Palette* p,unsigned c, double a);
		const Palette* p;
		const unsigned clr;
		double alpha;
		void updateAlpha(double newAlpha);
	};
	void remove(color* c);
	unsigned average(color c1, color c2, double i)const;
	std::list<color*> colors;
	friend class LutCursor;
//public:
	Palette();
	color* add(unsigned color, double alpha);
	unsigned operator[](double alpha)const;
	bool empty()const;
};

#endif
