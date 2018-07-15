#ifndef FUNCTIONWORKSPACE_H
#define FUNCTIONWORKSPACE_H

#include <Workspace.h>
#include "Function.h"

class FunctionWorkspace: public Workspace{
	class FunctionInputNode: public Node{

	};
	struct Socket: Node::Socket{
		Socket();
		~Socket();
		FunctionWorkspace* parent;
		void connectToNode(Node*);
		void disconnectNode();
	};
public:
	FunctionWorkspace(QWidget* parent=0);
	~FunctionWorkspace();
	uint nbArgs;
	Function* func;
	void setFunction(Function *fun);
private:
	Socket *outputSocket;
	void dragEnterEvent(QDragEnterEvent*);
};

#endif // FUNCTIONWORKSPACE_H
