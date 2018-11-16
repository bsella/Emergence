#include "LUTNode.h"
#include "dialog/lut_dialog.h"

void Gradient::toBin(std::ostream& out)const{
	uint n=0;
	for(auto it=first; it;it=it->next)
		n++;
	out.write(reinterpret_cast<const char*>(&n),sizeof(uint));
	for(auto it= first; it; it=it->next){
		out.write(reinterpret_cast<const char*>(&it->clr),sizeof(uint));
		out.write(reinterpret_cast<const char*>(&it->alpha),sizeof(double));
	}
}
void Gradient::toText(std::ostream& out)const{
	uint n=0;
	for(auto it=first; it;it=it->next)
		n++;
	out << n <<' ';
	for(auto it= first; it; it=it->next){
		out << it->clr <<' '<< it->alpha;
		if(it->next) out<<' ';
	}
}

Node* LUTNode::makeFromBin(std::istream&in){
	Gradient *g;
	if(in.peek()!=EOF){
		g= new Gradient;
		uint n;
		in.read(reinterpret_cast<char*>(&n),sizeof(uint));
		double alpha;
		data_t::color color;
		for(uint i=0;i<n;i++){
			in.read(reinterpret_cast<char*>(&color),sizeof(data_t::color));
			in.read(reinterpret_cast<char*>(&alpha),sizeof(double));
			g->add(color,alpha);
		}
	}
	else g= LutDialog::getGradient();
	if(g)return new LUTNode(g);
	return nullptr;
}
Node* LUTNode::makeFromText(std::istream&in){
	Gradient *g;
	if(in.peek()!=EOF){
		g= new Gradient;
		uint n;
		in>>n;
		double alpha;
		data_t::color color;
		for(uint i=0;i<n;i++){
			in >> color;
			in >> alpha;
			g->add(color,alpha);
		}
	}
	else g= LutDialog::getGradient();
	if(g)return new LUTNode(g);
	return nullptr;
}

void LUTNode::toBin(std::ostream &out)const{
	Node::toBin(out);
	gradient.toBin(out);
}
void LUTNode::toText(std::ostream &out)const{
	Node::toText(out);
	out<< ' ';
	gradient.toText(out);
}
