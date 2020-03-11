#include "multilevelqueuewindow.h"
#include "ui_multilevelqueuewindow.h"

MultilevelQueueWindow::MultilevelQueueWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultilevelQueueWindow)
{
    ui->setupUi(this);
}

MultilevelQueueWindow::~MultilevelQueueWindow()
{
    delete ui;
}

void MultilevelQueueWindow::on_backButton_clicked()
{
    emit backButtonClicked();
}
