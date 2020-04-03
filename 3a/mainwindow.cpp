#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "sorting.h"
#include <QDebug>
#include "functs.h"

#define n 100

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->insertWidget(1, &DW);
    ui->stackedWidget->insertWidget(2, &BW);
    connect(&DW, SIGNAL(backButtonClicked()), this, SLOT(toMainMenu()));
    connect(&BW, SIGNAL(backButtonClicked()), this, SLOT(toMainMenu()));

    //int arr[] = {5, 7, 10, 5, 24, 8, 1, 6, 3, 2, 13, 9, 4, 19, 15, 14};

    //int temp[9];

    int arr[n] = {};

    randomizeIntArray(arr, n, 1, n);



   mergeSort(arr, n);
   //hybridQuicksort(arr, 0, n-1, 10);

    for (int elem : arr) {
        qDebug() << elem;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toMainMenu()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_demoButton_clicked()
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
