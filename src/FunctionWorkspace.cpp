#include "headers/FunctionWorkspace.h"

FunctionWorkspace::FunctionWorkspace(const QString& name,QWidget *parent)
	:Workspace(parent), _name(name){
	functions.insert(this);
}
FunctionWorkspace::FunctionWorkspace(QWidget *parent)
	:FunctionWorkspace("new function",parent){
}
FunctionWorkspace::~FunctionWorkspace(){
	functions.remove(this);
}

QSet<FunctionWorkspace*> FunctionWorkspace::functions;
