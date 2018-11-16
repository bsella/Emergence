#pragma once

#include "ui_mainwindow.h"
#include "EmergenceInterface.h"

class PluginManager{
public:
	explicit PluginManager(Ui::MainWindow*);
	Ui::MainWindow *ui;
	bool loadPlugins();
	void toBin(std::ostream&)const;
	void toText(std::ostream&)const;
	void fromBin(std::istream&)const;
	void fromText(std::istream&)const;
	std::vector<EmergenceInterface*> plugins;
	std::vector<void(*)()> evalFunctions;
};
