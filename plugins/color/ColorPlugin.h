#ifndef COLORPLUGIN_H
#define COLORPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "NodeInterface.h"
#include "ColorNode.h"

class ColorPlugin: public QObject, NodeInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Emergence.Plugin")
	Q_INTERFACES(NodeInterface)
public:
	void updateUI(QMenu*, NodeBox*, Workspace*)const override;
	void addNodes()const override;
};

#endif
