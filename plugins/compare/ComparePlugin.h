#ifndef COMPAREPLUGIN_H
#define COMPAREPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "NodeInterface.h"
#include "CompNode.h"

class ComparePlugin: public QObject, NodeInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Emergence.Plugin")
	Q_INTERFACES(NodeInterface)
public:
	void updateUI(QMenu*, NodeBox*, Workspace*)const override;
	void addNodes()const;
};

#endif