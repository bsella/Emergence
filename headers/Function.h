#ifndef FUNCTION_H
#define FUNCTION_H

#include "nodes/Node.h"
#include "QGraphicsScene"
#include "QListWidgetItem"

class Function: public QListWidgetItem{
public:
	Function(const QString& name);
	Node* start;
	QGraphicsScene* scene;
};

#endif // FUNCTION_H
