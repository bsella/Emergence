#include "Gradient.h"
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

Gradient::Gradient(){}
Gradient::Gradient(const Gradient &p){
	if(!p.empty()){
		first= new color(p.first);
		color* tmp= first;
		for(color*tmpOther=p.first->next;tmpOther;tmpOther=tmpOther->next){
			tmp->next= new color(tmpOther);
			tmp->next->prev=tmp;
			tmp->next->gr=this;
			tmp=tmp->next;
		}
		last=tmp;
	}
}

Gradient::color::color(Gradient*g,unsigned c, double a):gr(g),clr(c), alpha(a){}
Gradient::color::color(color *c):clr(c->clr),alpha(c->alpha){}
void Gradient::color::updateAlpha(double newAlpha){
	if(next && newAlpha>next->alpha){
		if(this==gr->first)
			gr->first=next;
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
			prev=gr->last;
			prev->next=this;
			gr->last=this;
			next=nullptr;
		}
	}else if(prev && newAlpha<prev->alpha){
		if(this==gr->last)
			gr->last=prev;
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
			next=gr->first;
			next->prev=this;
			gr->first=this;
			prev=nullptr;
		}
	}
	alpha=newAlpha;
}

bool Gradient::empty()const{
	return first==nullptr;
}

Gradient::color *Gradient::add(unsigned color, double alpha){
	if(alpha<0)alpha=0;
	if(alpha>1)alpha=1;
	Gradient::color* n= new Gradient::color(this,color, alpha);
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

unsigned Gradient::average(color c1, color c2, double i){
	i=(i-c1.alpha)/(c2.alpha-c1.alpha);
	uint8_t r1,g1,b1, r2,g2,b2;
	getRGB(c1.clr, r1, g1, b1);
	getRGB(c2.clr, r2, g2, b2);

	return makeRGB(r2*i+(1.0-i)*r1
					,g2*i+(1.0-i)*g1
					,b2*i+(1.0-i)*b1);
}

unsigned Gradient::operator[](double alpha)const{
	if(empty()) return 0xff000000;
	if(alpha<0) return first->clr;
	if(alpha<first->alpha) return first->clr;
	for(auto it= first->next; it!= nullptr; it=it->next){
		if(alpha<it->alpha)
			return average(*it->prev, *it, alpha);
	}
	return last->clr;
}

void Gradient::remove(color *c){
	if(!c)return;
	if(c==first) first=c->next;
	else c->prev->next=c->next;
	if(c==last) last=c->prev;
	else c->next->prev=c->prev;
	delete c;
}
Gradient::~Gradient(){
	while (!empty()) remove(first);
}
std::ostream& operator<<(std::ostream& out,const Gradient&grd){
	uint n=0;
	for(auto it=grd.first; it;it=it->next)
		n++;
	out << n <<' ';
	for(auto it= grd.first; it; it=it->next){
		out << it->clr <<' '<< it->alpha;
		if(it->next) out<<' ';
	}
	return out;
}
