#pragma once

#include <QMenu>
#include "NodeBox.h"
#include "Workspace.h"

class NodeInterface{
public:
	virtual void updateUI(QMenu*, NodeBox*,Workspace*)const{}
	virtual void addNodes()const{}
};

#define Plugin_iid "Emergence.Plugin"

Q_DECLARE_INTERFACE(NodeInterface, Plugin_iid)
