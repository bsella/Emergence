#ifndef SHOWFRACTAL
#define SHOWFRACTAL
#include <list>

class Palette{
public:
	Palette();
    void add(unsigned color, double alpha);
    unsigned operator[](double alpha)const;
	bool empty()const;
private:
	struct color{
        color(unsigned c, double a);
        unsigned clr;
        double alpha;
        inline unsigned getClr()const{return clr;}
        inline double getAlpha()const{return alpha;}
	};
    unsigned average(color c1, color c2, double i)const;
	std::list<color> colors;
};

#endif
