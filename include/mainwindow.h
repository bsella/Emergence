#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShortcut>
#include "include/ExportImageDialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	QShortcut* copy;
	QShortcut* paste;

private slots:
	void on_actionExit_triggered();
	void on_actionExport_triggered();
	void on_actionSave_as_triggered();
	void on_actionOpen_triggered();
};

#endif // MAINWINDOW_H
