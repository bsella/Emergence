#pragma once

#include <QMenu>

#include "Workspace.h"
#include "ui_mainwindow.h"

class EmergenceInterface{
public:
	virtual void updateUI(Ui::MainWindow*)const{}
	virtual void init()const{}
	inline virtual bool redefineSaveLoad()const{return false;}
	virtual void toBin(std::ostream&)const{}
	virtual void toText(std::ostream&)const{}
	virtual void fromBin(std::istream&)const{}
	virtual void fromText(std::istream&)const{}
};

Q_DECLARE_INTERFACE(EmergenceInterface, "Emergence.Node.Plugin")
