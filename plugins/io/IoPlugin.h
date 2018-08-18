#ifndef IOPLUGIN_H
#define IOPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "NodeInterface.h"
#include "Node.h"
#include "InputNode.h"
#include "OutputNode.h"

class IoPlugin: public QObject, NodeInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Emergence.Plugin")
	Q_INTERFACES(NodeInterface)
public:
	void updateUI(QMenu*, NodeBox*, Workspace*)const override;
	void addNodes()const override;
};

#endif