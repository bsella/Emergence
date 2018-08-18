#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include <fstream>

#include <QPluginLoader>
#include <QFileDialog>
#include "Workspace.h"
#include "NodeInterface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
private:
	static const int _magic_number=0xa1b2affd;
	static const int _version=4;
	Ui::MainWindow *ui;
	Workspace* scene;
//	FunctionManager fm;
	QAction zoomIN, zoomOUT;
	bool loadPlugins();

private slots:
	void save()const;
	void load();
//	void updateActions();
	void zoomIn()const;
	void zoomOut()const;

	void on_actionExit_triggered();
};

#endif // MAINWINDOW_H
