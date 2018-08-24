#pragma once

#include "ui_mainwindow.h"
#include "EmergenceInterface.h"

class PluginManager{
public:
	explicit PluginManager(Ui::MainWindow*);
	Ui::MainWindow *ui;
	bool loadPlugins();
	void save(std::ostream&)const;
	void load(std::istream&)const;
	std::vector<EmergenceInterface*> plugins;
	std::vector<void(*)()> evalFunctions;
};
