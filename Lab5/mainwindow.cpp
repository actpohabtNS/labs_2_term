#include <QMessageBox>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mgraph.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->insertWidget(1, &_GW);
    ui->stackedWidget->insertWidget(2, &_BW);
    connect(&_GW, SIGNAL(backButtonClicked()), this, SLOT(toMainMenu()));
    connect(&_BW, SIGNAL(backButtonClicked()), this, SLOT(toMainMenu()));

    MGraph g1(8);
    g1.weighted(true);
    g1.addEdge(0, 1, 2);
    g1.addEdge(0, 2, 1);

    g1.addEdge(1,3,1);
    g1.addEdge(1,4,2);

    g1.addEdge(1,5,1);

    g1.addEdge(2,6,2);
    g1.addEdge(2,7,1);

    g1.kruskal()->print();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toMainMenu()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_graphsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_benchmarkButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_exitButton_clicked()
{
    QMessageBox::StandardButton exit = QMessageBox::question(this, "Close application", "Are you sure?",
                                                             QMessageBox::Yes | QMessageBox::No);
    if (exit == QMessageBox::Yes) QApplication::quit();
}
