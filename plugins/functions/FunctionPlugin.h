#ifndef FUNCPLUGIN_H
#define FUNCPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include "EmergenceInterface.h"

class FunctionPlugin: public QObject, EmergenceInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Emergence.Plugin")
	Q_INTERFACES(EmergenceInterface)
public:
	void updateUI(Ui::MainWindow*)const override;
	void init()const override;
	void save(std::ostream&)const override;
	void load(std::istream&)const override;
	inline bool redefineSaveLoad()const override{return true;}
};

#endif
