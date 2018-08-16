#pragma once

class NodeInterface{
public:
	virtual ~NodeInterface(){}
	virtual void initialize()=0;
};

#define Plugin_iid "Emergence.Plugin"

Q_DECLARE_INTERFACE(NodeInterface, Plugin_iid)
