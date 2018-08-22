#ifndef MATHPLUGIN_H
#define MATHPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "NodeInterface.h"
#include "Node.h"
#include "MathNode.h"
#include "RealNode.h"
#include "ComplexNode.h"

class MathPlugin: public QObject, NodeInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Emergence.Node.Plugin")
	Q_INTERFACES(NodeInterface)
public:
	void updateUI(Ui::MainWindow*)const override;
	void addNodes()const override;
};

#endif
