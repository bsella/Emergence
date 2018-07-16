#ifndef FUNCTION_H
#define FUNCTION_H

#include "nodes/Node.h"
#include "nodes/FunctionNode.h"
#include "QGraphicsScene"
#include "QListWidgetItem"

class Function: public QListWidgetItem{
public:
	struct InputNode: public Node{
		InputNode(uint rank);
		const uint _rank;
		inline data_t kernel()const{return currentFunction->iNodes[_rank]->eval();}
		void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
	};
	struct OutputNode: Node{
		OutputNode();
		inline data_t kernel()const{return iNodes[0];}
		void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
	};
	static FunctionNode* currentFunction;
	Function(const QString& name, uint nbArgs=0);
	~Function();
	uint nbArgs;
	OutputNode* start;
	QVector<InputNode*> iNodes;
	QGraphicsScene* scene;
};

#endif // FUNCTION_H
