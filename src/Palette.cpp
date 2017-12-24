#include "lib/Palette.h"

/*Uint32 = [........][..BLUE..][.GREEN..][...RED..]*/

void getRGB(unsigned color, char &r, char &g, char &b){
	b=color;
	color>>=8;
	g=color;
	color>>=8;
	r=color;
}

unsigned makeRGB(char r, char g, char b){
    unsigned c=0xff;
	c<<=8; c|=r;
	c<<=8; c|=g;
	c<<=8; c|=b;
	return c;
}

Palette::Palette(){}

Palette::color::color(unsigned c, double a): clr(c), alpha(a){}

bool Palette::empty()const{
	return colors.empty();
}

void Palette::add(unsigned color, double alpha){
	if(alpha<0)alpha=0;
	if(alpha>1)alpha=1;
	Palette::color n(color, alpha);
	if(empty())
		colors.push_back(n);
	else{
		if(colors.front().getAlpha() > alpha)
			colors.push_front(n);
		else{
			for(auto it =colors.begin(); it !=colors.end(); ++it)
				if(it->getAlpha() >= alpha){
					colors.insert(it,n);
					return;
				}
			colors.push_back(n);
		}
	}
}

unsigned Palette::average(color c1, color c2, double i)const{
	i=(i-c1.getAlpha())/(c2.getAlpha()-c1.getAlpha());
    char r1,g1,b1, r2,g2,b2;
	getRGB(c1.getClr(), r1, g1, b1);
	getRGB(c2.getClr(), r2, g2, b2);

	return makeRGB(r2*i+(1.0-i)*r1
					,g2*i+(1.0-i)*g1
					,b2*i+(1.0-i)*b1);
}

unsigned Palette::operator[](double alpha)const{
	if(empty()) return 0;
	if(alpha<0) return colors.front().getClr();
	if(alpha<colors.front().getAlpha()) return colors.front().getClr();
	for(auto it= colors.cbegin(); it != colors.cend(); ++it){
		if(std::next(it)->getAlpha()>=alpha)
			return average(*it, *std::next(it), alpha);
	}
	return colors.back().getClr();
}
