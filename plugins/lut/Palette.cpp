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
Palette::Palette(const Palette &p){
	if(!p.empty()){
		first= new color(p.first);
		color* tmp= first;
		for(color*tmpOther=p.first->next;tmpOther;tmpOther=tmpOther->next){
			tmp->next= new color(tmpOther);
			tmp->next->prev=tmp;
			tmp->next->plt=this;
			tmp=tmp->next;
		}
		last=tmp;
	}
}

Palette::color::color(Palette*p,unsigned c, double a):plt(p),clr(c), alpha(a){}
Palette::color::color(color *c):clr(c->clr),alpha(c->alpha){}
void Palette::color::updateAlpha(double newAlpha){
	if(next && newAlpha>next->alpha){
		if(this==plt->first)
			plt->first=next;
		else prev->next=next;
		next->prev=prev;

		color* tmp= next->next;
		while(tmp&&newAlpha>tmp->alpha)
			tmp=tmp->next;
		if(tmp){
			prev=tmp->prev;
			tmp->prev=this;
			prev->next=this;
			next=tmp;
		}else{
			prev=plt->last;
			prev->next=this;
			plt->last=this;
			next=nullptr;
		}
	}else if(prev && newAlpha<prev->alpha){
		if(this==plt->last)
			plt->last=prev;
		else next->prev=prev;
		prev->next=next;

		color* tmp= prev->prev;
		while(tmp&&newAlpha<tmp->alpha)
			tmp=tmp->prev;
		if(tmp){
			next=tmp->next;
			tmp->next=this;
			next->prev=this;
			prev=tmp;
		}else{
			next=plt->first;
			next->prev=this;
			plt->first=this;
			prev=nullptr;
		}
	}
	alpha=newAlpha;
}

bool Palette::empty()const{
	return first==nullptr;
}

Palette::color *Palette::add(unsigned color, double alpha){
	if(alpha<0)alpha=0;
	if(alpha>1)alpha=1;
	Palette::color* n= new Palette::color(this,color, alpha);
	if(empty())
		first=last=n;
	else{
		if(first->alpha > alpha){
			n->next=first;
			first->prev=n;
			first=n;
		}
		else{
			for(auto it =first; it !=nullptr; it=it->next)
				if(it->alpha >= alpha){
					struct color* before= it->prev;
					it->prev=n;
					before->next=n;
					n->prev=before;
					n->next=it;
					return n;
				}
			last->next=n;
			n->prev=last;
			last=n;
		}
	}
	return n;
}

unsigned Palette::average(color c1, color c2, double i){
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
	if(alpha<0) return first->clr;
	if(alpha<first->alpha) return first->clr;
	for(auto it= first->next; it!= nullptr; it=it->next){
		if(alpha<it->alpha)
			return average(*it->prev, *it, alpha);
	}
	return last->clr;
}

void Palette::remove(color *c){
	if(!c)return;
	if(c==first) first=c->next;
	else c->prev->next=c->next;
	if(c==last) last=c->prev;
	else c->next->prev=c->prev;
	delete c;
}
Palette::~Palette(){
	while (!empty()) remove(first);
}
