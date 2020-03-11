#include "priorityqueuewindow.h"
#include "ui_priorityqueuewindow.h"
#include "priorityqueue.h"
#include "task.h"
#include "table.h"
#include "functs.h"

PriorityQueueWindow::PriorityQueueWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PriorityQueueWindow)
{
    ui->setupUi(this);

    table taskListTable(ui->taskListTable);
    taskListTable.setSize(0, 60, {570}, {"Task title"});

}

PriorityQueueWindow::~PriorityQueueWindow()
{
    delete ui;
}

void PriorityQueueWindow::on_backButton_clicked()
{
    emit backButtonClicked();
}

void PriorityQueueWindow::on_loadStationDeepButton_clicked()
{
    setLabelText(ui->taskListNameLabel, "Station (Deep laying)");

    table taskListTable(ui->taskListTable);
    m_prQ = tasksToPrQ(getTasks("station_deep.txt"));
    taskListTable.setPrQ(m_prQ);

    setTaskButtonsEnabled(true);
}

void PriorityQueueWindow::on_loadStationShallowButton_clicked()
{
    setLabelText(ui->taskListNameLabel, "Station (Shallow laying)");

    table taskListTable(ui->taskListTable);
    m_prQ = tasksToPrQ(getTasks("station_shallow.txt"));
    taskListTable.setPrQ(m_prQ);

    setTaskButtonsEnabled(true);
}

void PriorityQueueWindow::on_loadTunnelDeepButton_clicked()
{
    setLabelText(ui->taskListNameLabel, "Tunnel (Deep laying)");

    table taskListTable(ui->taskListTable);
    m_prQ = tasksToPrQ(getTasks("tunnel_deep.txt"));
    taskListTable.setPrQ(m_prQ);

    setTaskButtonsEnabled(true);
}

void PriorityQueueWindow::on_loadTunnelShallowButton_clicked()
{
    setLabelText(ui->taskListNameLabel, "Tunnel (Shallow laying)");

    table taskListTable(ui->taskListTable);
    m_prQ = tasksToPrQ(getTasks("tunnel_shallow.txt"));
    taskListTable.setPrQ(m_prQ);

    setTaskButtonsEnabled(true);
}

void PriorityQueueWindow::on_addTaskListButton_clicked()
{
    ui->taskListTable->clear();

    QString taskListName = ui->taskListNameInput->text();

    if (taskListName == "") {
        taskListName = "Task list №" + QString::number(getRandomInt(1000, 9999));
    }

    setLabelText(ui->taskListNameLabel, taskListName);

    m_prQ = PriorityQueue<QString>();

    setTaskButtonsEnabled(true);

}

void PriorityQueueWindow::on_addTaskButton_clicked()
{
    QString taskName = ui->taskNameInput->text();

    if (taskName == "") {
        taskName = "Task №" + QString::number(getRandomInt(1000, 9999));
    }

    uint prior = ui->taskPriorInput->value();

    m_prQ.push(taskName, prior);

    table taskListTable(ui->taskListTable);
    taskListTable.setPrQ(m_prQ);
}

void PriorityQueueWindow::on_removeTaskButton_clicked()
{
    table taskListTable(ui->taskListTable);

    QString removingTask = taskListTable.selectedItems()[0]->text();

    m_prQ.remove(&removingTask);

    taskListTable.setPrQ(m_prQ);
}

void PriorityQueueWindow::setTaskButtonsEnabled(bool enabled)
{
    ui->addTaskButton->setEnabled(enabled);
    ui->removeTaskButton->setEnabled(enabled);
}
