#pragma once

#include "ui_mainwindow.h"
#include "NodeInterface.h"

class PluginManager{
public:
	explicit PluginManager(Ui::MainWindow*);
	static PluginManager* singleton;
	Ui::MainWindow *ui;
	bool loadPlugins();
	void save(std::ostream&)const;
	void load(std::istream&)const;
	std::vector<NodeInterface*> plugins;
	std::vector<void(*)()> evalFunctions;
};
