#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->insertWidget(1, &prQW);

    ui->stackedWidget->insertWidget(2, &mlQW);


    connect(&prQW, SIGNAL(backButtonClicked()), this, SLOT(toMainMenu()));

    connect(&mlQW, SIGNAL(backButtonClicked()), this, SLOT(toMainMenu()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_priorityQueueButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_multilevelQueueButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::toMainMenu()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_exitButton_clicked()
{
    QMessageBox::StandardButton exit = QMessageBox::question(this, "", "Are you sure?",
                                                             QMessageBox::Yes | QMessageBox::No);

    if (exit == QMessageBox::Yes) QApplication::quit();
}
