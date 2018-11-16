#include "ColorNode.h"
#include <QColorDialog>

static Node* askForColor(){
	QColor c= QColorDialog::getColor(Qt::white);
	if(c.isValid())
		return new ColorNode(c.rgba());
	return nullptr;
}

Node* ColorNode::makeFromBin(std::istream& in){
	if(in.peek()!=EOF){
		data_t::color clr;
		in.read(reinterpret_cast<char*>(&clr),sizeof(data_t::color));
		return new ColorNode(clr);
	}
	return askForColor();
}

Node* ColorNode::makeFromText(std::istream& in){
	if(in.peek()!=EOF){
		data_t::color clr;
		in>>clr;
		return new ColorNode(clr);
	}
	return askForColor();
}

void ColorNode::toBin(std::ostream &out) const{
	Node::toBin(out);
	out.write(reinterpret_cast<const char*>(&cache.clr),sizeof(data_t::color));
}

void ColorNode::toText(std::ostream &out) const{
	Node::toText(out);
	out <<' '<<cache.clr;
}
