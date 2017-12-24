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
    FuncGate* red= new ConstGate(0xffff0000);
    FuncGate* green= new ConstGate(0xff00ff00);
    FuncGate* c = new ConstGate(.75);
    FuncGate* gt = new GTGate;
    FuncGate* ifg = new IfGate;
    FuncGate *y= ui->widget->yg;
    RenderGate*s= ui->widget->start;

    gt->setPos(100,50);
    y->setY(100);
    ifg->setPos(200,30);
    red->setPos(100,-50);
    green->setPos(100,150);
    s->setPos(280,50);
    scene->addItem(s);
    scene->addItem(red);
    scene->addItem(green);
    scene->addItem(c);
    scene->addItem(gt);
    scene->addItem(ifg);
    scene->addItem(y);
    //gt->connect(x,0);
    //gt->connect(y,1);
}

MainWindow::~MainWindow(){
    delete ui;
}
