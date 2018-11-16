#ifndef FUNCTION_H
#define FUNCTION_H

#include "Node.h"
#include <QListWidgetItem>
#include "Workspace.h"

class Function: public QListWidgetItem{
public:
	struct FunctionInputNode: public Node{
		FunctionInputNode(int rank);
		const int _rank;
		data_t kernel()const;
		void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
		void toBin(std::ostream &)const;
		void toText(std::ostream &)const;
		static Node* makeNode(std::istream&);
	};
	struct FunctionOutputNode: Node{
		FunctionOutputNode();
		inline data_t kernel()const{return iNodes[0]->eval();}
		inline static Node* makeNode(std::istream&){return new FunctionOutputNode;}
		void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
	};
	Function(int,const QString&);
	Function();
	~Function();
	int nbArgs;
	FunctionOutputNode* start;
	QVector<FunctionInputNode*> iNodes;
	Workspace* scene;
	void toBin(std::ostream& out)const;
	void toText(std::ostream& out)const;
	FunctionOutputNode* getOutputFromScene()const;
	FunctionInputNode* getNthInputFromScene(int n)const;
};


#endif // FUNCTION_H
