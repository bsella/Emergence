#ifndef IMAGEPLUGIN_H
#define IMAGEPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "NodeInterface.h"
#include "Node.h"
#include "BitmapNode.h"

class ImagePlugin: public QObject, NodeInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Emergence.Plugin")
	Q_INTERFACES(NodeInterface)
public:
	void updateUI(QMenu*, NodeBox*, Workspace*)const override;
	void addNodes()const;
};

#endif
