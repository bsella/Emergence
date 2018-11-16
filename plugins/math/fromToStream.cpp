#include "RealNode.h"

Node* RealNode::makeFromBin(std::istream &in){
	if(in.peek()!=EOF){
		double d;
		in.read(reinterpret_cast<char*>(&d) ,sizeof(double));
		return new RealNode(d);
	}
	return new RealNode;
}
Node* RealNode::makeFromText(std::istream &in){
	if(in.peek()!=EOF){
		double d;
		in>>d;
		return new RealNode(d);
	}
	return new RealNode;
}

void RealNode::toBin(std::ostream &out) const{
	Node::toBin(out);
	out.write(reinterpret_cast<const char*>(&cache.d),sizeof(double));
}
void RealNode::toText(std::ostream &out) const{
	Node::toText(out);
	out <<' '<< cache.d;
}
