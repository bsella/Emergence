#include "FunctionNode.h"
#include "FunctionManager.h"

Node* Function::FunctionInputNode::makefromBin(std::istream &in){
	int r;
	in.read(reinterpret_cast<char*>(&r),sizeof(int));
	return new FunctionInputNode(r);
}
Node* Function::FunctionInputNode::makefromText(std::istream &in){
	int r;
	in >>r;
	return new FunctionInputNode(r);
}

void Function::FunctionInputNode::toBin(std::ostream&out)const{
	Node::toBin(out);
	out.write(reinterpret_cast<const char*>(&_rank),sizeof(int));
}
void Function::FunctionInputNode::toText(std::ostream&out)const{
	Node::toText(out);
	out <<' '<< _rank;
}

void Function::toBin(std::ostream& out)const{
	const std::string tmp= text().toStdString();
	out.write(tmp.data(),sizeof(char)*tmp.size());
	out << '\n';
	scene->toBin(out);
	out.write(reinterpret_cast<const char*>(&nbArgs),sizeof(int));
}

void Function::toText(std::ostream& out)const{
	out << text().toStdString()<<"\n";
	scene->toText(out);
	out << nbArgs << '\n';
}

Node* FunctionNode::makefromBin(std::istream&in){
	Function* f;
	if(in.peek()!=EOF){
		int i;
		in.read(reinterpret_cast<char*>(&i),sizeof(int));
		f=FunctionManager::functionAt(i);
	}else{
		f=FunctionManager::getFunction();
		if(!f) return nullptr;
	}
	return new FunctionNode(f);
}
Node* FunctionNode::makefromText(std::istream&in){
	Function* f;
	if(in.peek()!=EOF){
		int i;
		in >> i;
		f=FunctionManager::functionAt(i);
	}else{
		f=FunctionManager::getFunction();
		if(!f) return nullptr;
	}
	return new FunctionNode(f);
}

void FunctionNode::toBin(std::ostream &out) const{
	Node::toBin(out);
	const int tmp= FunctionManager::indexOf(func);
	out.write(reinterpret_cast<const char*>(&tmp),sizeof(int));
}
void FunctionNode::toText(std::ostream &out) const{
	Node::toText(out);
	out <<' '<< FunctionManager::indexOf(func);
}
