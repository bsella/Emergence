#ifndef LUTPLUGIN_H
#define LUTPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "EmergenceInterface.h"

class LUTPlugin: public QObject, EmergenceInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Emergence.Plugin")
	Q_INTERFACES(EmergenceInterface)
public:
	void updateUI(Ui::MainWindow*)const override;
	void init()const override;
};

#endif
