#ifndef FUNCTIONMANAGER_H
#define FUNCTIONMANAGER_H

#include <QMainWindow>

namespace Ui {
class FunctionManager;
}

class FunctionManager : public QMainWindow
{
	Q_OBJECT

public:
	explicit FunctionManager(QWidget *parent = 0);
	~FunctionManager();

private:
	Ui::FunctionManager *ui;
};

#endif // FUNCTIONMANAGER_H
