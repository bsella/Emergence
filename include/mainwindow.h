#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "include/ExportImageDialog.h"
#include <memory>

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

private slots:
	void exportImage();
};

#endif // MAINWINDOW_H
