#ifndef CONDITIONPLUGIN_H
#define CONDITIONPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "EmergenceInterface.h"

class ConditionPlugin: public QObject, EmergenceInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Emergence.Plugin")
	Q_INTERFACES(EmergenceInterface)
public:
	void updateUI(Ui::MainWindow*)const override;
	void init()const;
};

#endif
