#ifndef COLORPLUGIN_H
#define COLORPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "EmergenceInterface.h"

class ColorPlugin: public QObject, EmergenceInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Emergence.Plugin")
	Q_INTERFACES(EmergenceInterface)
public:
	void updateUI(Ui::MainWindow*)const override;
	void init()const override;
};

#endif
