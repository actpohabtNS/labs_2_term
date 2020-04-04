#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "sorting.h"
#include <QDebug>
#include "functs.h"
#include "date.h"
#include "benchmark.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->insertWidget(1, &DW);
    ui->stackedWidget->insertWidget(2, &BW);
    connect(&DW, SIGNAL(backButtonClicked()), this, SLOT(toMainMenu()));
    connect(&BW, SIGNAL(backButtonClicked()), this, SLOT(toMainMenu()));

    int n = 260468;

    //Date* arr = getRandomDateArray(n);
    int* arr = createRandomIntArray(n);

//    for (int i = 0; i < n; i++) {
//            qDebug() << arr[i];
//        }

    qDebug() << benchSortAlg(mergesort, arr, n);

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
