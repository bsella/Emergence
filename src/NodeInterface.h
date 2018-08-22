#pragma once

#include <QMenu>

#include "Workspace.h"
#include "ui_mainwindow.h"

class NodeInterface{
public:
	virtual void updateUI(Ui::MainWindow*)const{}
	virtual void addNodes()const{}
	inline bool redefineSaveLoad()const{return false;}
	static void save(std::ostream&){}
	static void load(std::istream&){}
};

Q_DECLARE_INTERFACE(NodeInterface, "Emergence.Node.Plugin")
