#ifndef FUNCTIONMANAGER_H
#define FUNCTIONMANAGER_H

#include <QDialog>
#include <QInputDialog>
#include <QListWidgetItem>
#include "Function.h"

namespace Ui {
class FunctionManager;
}

class FunctionManager : public QDialog{
	Q_OBJECT

public:
	explicit FunctionManager(QWidget *parent = 0);
	~FunctionManager();
	void addFunction(const QString& name, uint nbArgs);

private:
	Ui::FunctionManager *ui;
private slots:
	void renameFunction(QListWidgetItem*);
};

#endif // FUNCTIONMANAGER_H
