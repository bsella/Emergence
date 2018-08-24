#ifndef MATHPLUGIN_H
#define MATHPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "EmergenceInterface.h"

class MathPlugin: public QObject, EmergenceInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Emergence.Node.Plugin")
	Q_INTERFACES(EmergenceInterface)
public:
	void updateUI(Ui::MainWindow*)const override;
	void init()const override;
};

#endif
