#ifndef IMAGEPLUGIN_H
#define IMAGEPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "NodeInterface.h"

class ImagePlugin: public QObject, NodeInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Emergence.Plugin")
	Q_INTERFACES(NodeInterface)
public:
	void updateUI(Ui::MainWindow*)const override;
	void init()const;
};

#endif
