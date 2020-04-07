#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "train.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    ui->stackedWidget->insertWidget(1, &administrateWindow);
    ui->stackedWidget->insertWidget(2, &demoWindow);
    ui->stackedWidget->insertWidget(3, &testsWindow);

    connect(&administrateWindow, SIGNAL(backButtonClicked()), this, SLOT(toMainMenu()));
    connect(&testsWindow, SIGNAL(backButtonClicked()), this, SLOT(toMainMenu()));

    ui->stackedWidget->setCurrentIndex(0);

//    train t1(123, 34, "Aaa", "Odesa", "Cbb", {11, 35}, {12, 34}, 0.8);
//    train t2(124, 34, "BBb", "Odesa", "Bbb", {11, 34}, {12, 34}, 0.5);

//    qDebug() << sequenceGreater({"arrTime", "type", "rate"}, t1, t2);

}

void MainWindow::on_administrateButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_demoButton_clicked()
{
    ui->stackedWidget->removeWidget(&demoWindow);

    Administrate* demoWindow = new Administrate(this, true);
    ui->stackedWidget->insertWidget(2, demoWindow);
    connect(demoWindow, SIGNAL(backButtonClicked()), this, SLOT(toMainMenu()));

    ui->stackedWidget->setCurrentIndex(2);

}

void MainWindow::on_testsButton_clicked()
{

    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_exitButton_clicked()
{
    QMessageBox::StandardButton exit = QMessageBox::question(this, "", "Are you sure?",
                                                             QMessageBox::Yes | QMessageBox::No);
    if (exit == QMessageBox::Yes) QApplication::quit();
}

void MainWindow::toMainMenu()
{
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}




