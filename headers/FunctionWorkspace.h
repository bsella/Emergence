#ifndef FUNCTIONWORKSPACE_H
#define FUNCTIONWORKSPACE_H

#include <Workspace.h>
#include "nodes/Node.h"

class FunctionWorkspace: public Workspace{
public:
	FunctionWorkspace(const QString& name,QWidget* parent=0);
	FunctionWorkspace(QWidget* parent=0);
	~FunctionWorkspace();
	uint nbArgs;
	QString _name;
	static QSet<FunctionWorkspace*> functions;
private:
	Node* start;
	friend class FunctionNode;
};

#endif // FUNCTIONWORKSPACE_H
