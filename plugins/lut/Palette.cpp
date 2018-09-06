#include "Palette.h"
#include <cstdint>
/*Uint32 = [.ALPHA..][...RED..][.GREEN..][..BLUE..]*/

void getRGB(unsigned color, uint8_t &r, uint8_t &g, uint8_t &b){
	b=color;
	color>>=8;
	g=color;
	color>>=8;
	r=color;
}

unsigned makeRGB(uint8_t r, uint8_t g, uint8_t b){
	unsigned c=0xff;
	c<<=8; c|=r;
	c<<=8; c|=g;
	c<<=8; c|=b;
	return c;
}

Palette::Palette(){}

Palette::color::color(Palette *p, unsigned c, double a): p(p),clr(c), alpha(a){}

bool Palette::empty()const{
	return colors.empty();
}

Palette::color *Palette::add(unsigned color, double alpha){
	if(alpha<0)alpha=0;
	if(alpha>1)alpha=1;
	Palette::color* n= new Palette::color(this,color, alpha);
	if(empty())
		colors.push_back(n);
	else{
		if(colors.front()->alpha > alpha)
			colors.push_front(n);
		else{
			for(auto it =colors.begin(); it !=colors.end(); ++it)
				if((*it)->alpha >= alpha){
					colors.insert(it,n);
					return n;
				}
			colors.push_back(n);
		}
	}
	return n;
}

unsigned Palette::average(color c1, color c2, double i)const{
	i=(i-c1.alpha)/(c2.alpha-c1.alpha);
	uint8_t r1,g1,b1, r2,g2,b2;
	getRGB(c1.clr, r1, g1, b1);
	getRGB(c2.clr, r2, g2, b2);

	return makeRGB(r2*i+(1.0-i)*r1
					,g2*i+(1.0-i)*g1
					,b2*i+(1.0-i)*b1);
}

unsigned Palette::operator[](double alpha)const{
	if(empty()) return 0xff000000;
	if(alpha<0) return colors.front()->clr;
	if(alpha<colors.front()->alpha) return colors.front()->clr;
	for(auto it= colors.cbegin(); std::next(it) != colors.cend(); ++it){
		if((*std::next(it))->alpha>=alpha)
			return average(**it, **std::next(it), alpha);
	}
	return colors.back()->clr;
}

void Palette::remove(color *c){
	colors.remove(c);
	delete c;
}
