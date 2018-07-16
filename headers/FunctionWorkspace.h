#ifndef FUNCTIONWORKSPACE_H
#define FUNCTIONWORKSPACE_H

#include <Workspace.h>
#include "Function.h"

class FunctionWorkspace: public Workspace{
public:
	FunctionWorkspace(QWidget* parent=0);
	~FunctionWorkspace();
	uint nbArgs;
	Function* func;
	void setFunction(Function *fun);
private:
	void updateFunctionNodes()const;
	void dragEnterEvent(QDragEnterEvent*);
	void resizeEvent(QResizeEvent*);
	void wheelEvent(QWheelEvent*);
};

#endif // FUNCTIONWORKSPACE_H
