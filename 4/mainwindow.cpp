#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "generalTree.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Node<int>* root = new Node<int>(1);
    root->insert({}, 2);
    root->insert({}, 5);
    root->insert({}, 8);
    root->insert({}, 88);
    root->insert({}, 888);
    root->insert({}, 8888);
    root->insert({}, 88888);
    root->insert({}, 888888);
    root->insert({}, 8888888);
    root->insert({}, 88888888);
    root->insert({}, 888888888);
    root->insert({0}, 3);
    root->insert({0}, 4);
    root->insert({0}, 9);
    root->insert({0, 0}, 11);
    root->insert({0, 2}, 10);
    root->insert({1}, 6);
    root->insert({1, 0}, 11);
    root->insert({1}, 7);


    //qDebug() << root->get({0});

    qDebug().noquote() << root->getSubtreeQStr(root->getMaxChildrenMap());
//    std::vector<int> path = root->getPath(10);

//    qDebug() << "FINAL PATH:";
//    for (int idx : path)
//    {
//        qDebug() << idx;
//    }


//    root->print();

//    qDebug() << "manipulating";
//    root->remove(11);

    //root->print();

//    std::vector<int> maxes = root->getMaxChildrenMap();

//    qDebug() << "=========";

//    for (int max : maxes)
//    {
//        qDebug() << max;
//    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

