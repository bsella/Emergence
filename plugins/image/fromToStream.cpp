#include "BitmapNode.h"
#include <QFileDialog>

Node* BitmapNode::makeFromBin(std::istream&in){
	if(in.peek()!=EOF){
		std::string path;
		in >> path;
		in.ignore(1);
		return new BitmapNode(path);
	}
	QString filename = QFileDialog::getOpenFileName(0,"Choose Image",".","Images (*.bmp)");
	if(filename.isNull()) return nullptr;
	return new BitmapNode(filename.toStdString());
}
Node* BitmapNode::makeFromText(std::istream&in){
	if(in.peek()!=EOF){
		std::string path;
		in >> path;
		return new BitmapNode(path);
	}
	QString filename = QFileDialog::getOpenFileName(0,"Choose Image",".","Images (*.bmp)");
	if(filename.isNull()) return nullptr;
	return new BitmapNode(filename.toStdString());
}

void BitmapNode::toBin(std::ostream &out) const{
	Node::toBin(out);
	out <<' '<< path << '\n';
}
void BitmapNode::toText(std::ostream &out) const{
	Node::toText(out);
	out <<' '<< path;
}
