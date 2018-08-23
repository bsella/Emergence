#ifndef FUNCTION_H
#define FUNCTION_H

#include "Node.h"
#include <QGraphicsScene>
#include <QListWidgetItem>
#include "Workspace.h"

class Function: public QListWidgetItem{
public:
	struct FunctionInputNode: public Node{
		FunctionInputNode(uint rank);
		const int _rank;
		data_t kernel()const;
		void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
		void toBin(std::ostream &)const;
	};
	struct FunctionOutputNode: Node{
		FunctionOutputNode();
		inline data_t kernel()const{return iNodes[0]->eval();}
		void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
	};
	Function(int,const QString&);
	Function();
	~Function();
	int nbArgs;
	FunctionOutputNode* start;
	QVector<FunctionInputNode*> iNodes;
	Workspace* scene;
	friend std::ostream& operator<<(std::ostream& out, const Function&f);
	FunctionOutputNode* getOutputFromScene()const;
	FunctionInputNode* getNthInputFromScene(int n)const;
};


#endif // FUNCTION_H
