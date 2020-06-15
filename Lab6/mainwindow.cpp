#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "arrayList.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ArrayList<int> list;

    list.push(1);
    list.push(2);
    list.push(8);
    list.push(4);
    list.push(1);
    list.push(6);

    qDebug()<< list.exist(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}

