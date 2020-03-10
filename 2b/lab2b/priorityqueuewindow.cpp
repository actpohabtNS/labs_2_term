#include "priorityqueuewindow.h"
#include "ui_priorityqueuewindow.h"
#include "priorityqueue.h"
#include "task.h"
#include "functs.h"

PriorityQueueWindow::PriorityQueueWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PriorityQueueWindow)
{
    ui->setupUi(this);

    PriorityQueue<QString> stationDeepPrQ = tasksToPrQ(getTasks("station_deep.txt"));

    stationDeepPrQ.print();

}

PriorityQueueWindow::~PriorityQueueWindow()
{
    delete ui;
}

void PriorityQueueWindow::on_backButton_clicked()
{
    emit backButtonClicked();
}
