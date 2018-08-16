#ifndef LOGICPLUGIN_H
#define LOGICPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "NodeInterface.h"

class LogicPlugin: public QObject, NodeInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Emergence.Plugin")
	Q_INTERFACES(NodeInterface)
public:
	LogicPlugin();
	void initialize()override;
};

#endif
