#ifndef FUNCTIONMANAGER_H
#define FUNCTIONMANAGER_H

#include <QDialog>
#include <QInputDialog>
#include <QListWidgetItem>
#include <QDialogButtonBox>
#include "Function.h"
#include "nodes/FunctionNode.h"

namespace Ui {
class FunctionManager;
}

class FunctionManager : public QDialog{
	Q_OBJECT

public:
	explicit FunctionManager(QWidget *parent = 0);
	~FunctionManager();
	static Function* getFunction(FunctionNode* node=0);
	static FunctionManager* singleton;
private:
	Ui::FunctionManager *ui;
private slots:
	void addNewFunction()const;
	void removeCurrentFunction()const;
	void renameFunction(QListWidgetItem*);
	void on_spinBox_valueChanged(int arg1);
};

#endif // FUNCTIONMANAGER_H
