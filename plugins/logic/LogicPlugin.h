#ifndef LOGICPLUGIN_H
#define LOGICPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "NodeInterface.h"
#include "LogicNode.h"

class LogicPlugin: public QObject, NodeInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Emergence.Plugin")
	Q_INTERFACES(NodeInterface)
public:
	void updateUI(Ui::MainWindow*)const override;
	void addNodes()const;
};

#endif
