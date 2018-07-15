#include "headers/Function.h"

Function::Function(const QString &name):QListWidgetItem(name){
	scene= new QGraphicsScene;
}
