#include "priorityqueuewindow.h"
#include "ui_priorityqueuewindow.h"
#include "priorityqueue.h"
#include "task.h"
#include "table.h"
#include "functs.h"
#include <QMessageBox>
#include <QTimer>

PriorityQueueWindow::PriorityQueueWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PriorityQueueWindow)
{
    ui->setupUi(this);

    table taskListTable(ui->taskListTable);
    taskListTable.setSize(0, 60, {40, 520}, {"Prior", "Task title"});

    m_randomEvents = getTasks("random_events.txt");

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

    enableRandomEvents();

    setTaskButtonsEnabled(true);
}

void PriorityQueueWindow::on_loadStationShallowButton_clicked()
{
    setLabelText(ui->taskListNameLabel, "Station (Shallow laying)");

    table taskListTable(ui->taskListTable);
    m_prQ = tasksToPrQ(getTasks("station_shallow.txt"));
    taskListTable.setPrQ(m_prQ);

    enableRandomEvents();

    setTaskButtonsEnabled(true);
}

void PriorityQueueWindow::on_loadTunnelDeepButton_clicked()
{
    setLabelText(ui->taskListNameLabel, "Tunnel (Deep laying)");

    table taskListTable(ui->taskListTable);
    m_prQ = tasksToPrQ(getTasks("tunnel_deep.txt"));
    taskListTable.setPrQ(m_prQ);

    enableRandomEvents();

    setTaskButtonsEnabled(true);
}

void PriorityQueueWindow::on_loadTunnelShallowButton_clicked()
{
    setLabelText(ui->taskListNameLabel, "Tunnel (Shallow laying)");

    table taskListTable(ui->taskListTable);
    m_prQ = tasksToPrQ(getTasks("tunnel_shallow.txt"));
    taskListTable.setPrQ(m_prQ);

    enableRandomEvents();

    setTaskButtonsEnabled(true);
}

void PriorityQueueWindow::on_addTaskListButton_clicked()
{
    table taskListTable(ui->taskListTable);

    taskListTable.clear();
    taskListTable.setSize(0, 60, {40, 520}, {"Prior", "Task title"});

    QString taskListName = ui->taskListNameInput->text();

    if (taskListName == "") {
        taskListName = "Task list №" + QString::number(getRandomInt(1000, 9999));
    }

    setLabelText(ui->taskListNameLabel, taskListName);

    m_prQ = PriorityQueue<QString>();

    enableRandomEvents();

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

    QString removingTask = ui->taskListTable->item(ui->taskListTable->selectedItems()[0]->row(), 1)->text();

    m_prQ.remove(&removingTask);

    taskListTable.setPrQ(m_prQ);
}

void PriorityQueueWindow::on_addRandomEventButton_clicked()
{

    if (m_randomEvents.size() == 0) {
       setLabelText(ui->errorLabel, "No random events left!");
       ui->addRandomEventButton->setEnabled(false);
       return;
    }

    int eventNum = getRandomInt(0, m_randomEvents.size()-1);
    m_prQ.push(m_randomEvents[eventNum]->title, m_randomEvents[eventNum]->priority);
    table taskListTable(ui->taskListTable);
    taskListTable.setPrQ(m_prQ);

    m_randomEvents.erase(m_randomEvents.begin() + eventNum);

}

void PriorityQueueWindow::setTaskButtonsEnabled(bool enabled)
{
    ui->addTaskButton->setEnabled(enabled);
    ui->removeTaskButton->setEnabled(enabled);
    ui->addRandomEventButton->setEnabled(enabled);
}

void PriorityQueueWindow::enableRandomEvents()
{
    m_randomEvents = getTasks("random_events.txt");
    setLabelText(ui->errorLabel, "");
    ui->addRandomEventButton->setEnabled(true);
}

void PriorityQueueWindow::on_demoButton_clicked()
{
    if (ui->taskListTable->rowCount() != 0) {

        QMessageBox::StandardButton exit = QMessageBox::question(this, "Start demo mode", "Task list table is not empty. If you start demo mode, all data will be deleted. Are you sure?",
                                                                 QMessageBox::Yes | QMessageBox::No);

        if (exit == QMessageBox::No) return;

    }

    ui->demoModeLabel->setText("Demonstration mode");

    ui->backButton->setEnabled(false);

    table taskListTable(ui->taskListTable);

    taskListTable.clear();
    taskListTable.setSize(0, 60, {40, 520}, {"Prior", "Task title"});

    QTimer::singleShot(1000, this, SLOT(on_loadStationDeepButton_clicked()));
    QTimer::singleShot(3000, this, SLOT(on_addRandomEventButton_clicked()));
    QTimer::singleShot(3300, this, SLOT(on_addRandomEventButton_clicked()));
    QTimer::singleShot(3600, this, SLOT(on_addRandomEventButton_clicked()));
    QTimer::singleShot(3900, this, SLOT(on_addRandomEventButton_clicked()));
    QTimer::singleShot(4200, this, SLOT(on_addRandomEventButton_clicked()));
    QTimer::singleShot(6000, this, SLOT(on_addRandomEventButton_clicked()));
    QTimer::singleShot(8000, this, [this]{ui->taskListNameInput->setText("My students' labs");});
    QTimer::singleShot(10000, this, SLOT(on_addTaskListButton_clicked()));
    QTimer::singleShot(11000, this, [this]{ui->taskPriorInput->setValue(4);});
    QTimer::singleShot(12000, this, SLOT(on_addTaskButton_clicked()));
    QTimer::singleShot(13000, this, [this]{ui->taskPriorInput->setValue(2);});
    QTimer::singleShot(14000, this, SLOT(on_addTaskButton_clicked()));
    QTimer::singleShot(15000, this, [this]{ui->taskPriorInput->setValue(2);});
    QTimer::singleShot(16000, this, SLOT(on_addTaskButton_clicked()));
    QTimer::singleShot(17000, this, [this]{ui->taskPriorInput->setValue(5);});
    QTimer::singleShot(18000, this, SLOT(on_addTaskButton_clicked()));
    QTimer::singleShot(20000, this, [this]{ui->taskListTable->selectRow(2);});
    QTimer::singleShot(22000, this, SLOT(on_removeTaskButton_clicked()));

    QTimer::singleShot(22500, this, [this]{
        ui->demoModeLabel->setText("");
        ui->backButton->setEnabled(true);
    });


}
