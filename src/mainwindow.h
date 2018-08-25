#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include <fstream>

#include <QPluginLoader>
#include <QFileDialog>
#include "Workspace.h"
#include "PluginManager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	Ui::MainWindow *ui;
private:
	static const int _magic_number=0xa1b2affd;
	static const int _version=5;
	Workspace* scene;
	PluginManager *pluginManager;
	QAction zoomIN, zoomOUT;
	QString _filePath="<untitled>";
	bool fileModified=false;
	void closeEvent(QCloseEvent*)override;
private slots:
	bool save();
	bool saveAs();
	void load();
//	void updateActions();
	void zoomIn()const;
	void zoomOut()const;
	void updateModified();

	void on_actionExit_triggered();
};

#endif // MAINWINDOW_H
