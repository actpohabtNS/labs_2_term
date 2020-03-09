#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->stackedWidget->insertWidget(1, &iW);

    ui->stackedWidget->insertWidget(2, &dW);

    ui->stackedWidget->insertWidget(3, &bW);

    connect(&iW, SIGNAL(backButtonClicked()), this, SLOT(toMainMenu()));

    connect(&bW, SIGNAL(backButtonClicked()), this, SLOT(toMainMenu()));


    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_interactButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_demoButton_clicked()
{

    ui->stackedWidget->removeWidget(&dW);

    interactWindow* dW = new interactWindow(this, true);

    ui->stackedWidget->insertWidget(2, dW);

    connect(dW, SIGNAL(backButtonClicked()), this, SLOT(toMainMenu()));

    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_benchmarkButton_clicked()
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
