#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lib/RenderArea.h"
#include "lib/CompGate.h"
#include "lib/PaletteGate.h"
#include "lib/IfGate.h"
#include "lib/ConstGate.h"

#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    QWidget::setWindowTitle("PixelGates");
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    Palette p;
    //p.add();
    FuncGate* gt = new GTGate;
    gt->setPos(100,50);
    //FuncGate *x= ui->widget->xg;
    FuncGate *y= ui->widget->yg;
    RenderGate*s= ui->widget->start;

    FuncGate *c= new ConstGate(0xffff0000);
    //s->connect(c,0);
    scene->addItem(s);
    scene->addItem(c);
    scene->addItem(y);
    scene->addItem(gt);
    y->setY(100);
    //gt->connect(x,0);
    //gt->connect(y,1);
}

MainWindow::~MainWindow(){
    delete ui;
}
