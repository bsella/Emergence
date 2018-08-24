#ifndef IOPLUGIN_H
#define IOPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "EmergenceInterface.h"

class IoPlugin: public QObject, EmergenceInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Emergence.Plugin")
	Q_INTERFACES(EmergenceInterface)
public:
	void updateUI(Ui::MainWindow*)const override;
	void init()const override;
};

#endif
