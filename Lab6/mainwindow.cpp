#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "linkedList.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LinkedList<int> list;

    list.push(1);
    list.push(2);
    list.push(8);
    list.push(4);
    list.push(1);
    list.push(6);

    list.print();
}

MainWindow::~MainWindow()
{
    delete ui;
}

