#include "multilevelqueuewindow.h"
#include "ui_multilevelqueuewindow.h"
#include "queue.h"
#include <QMessageBox>
#include <QTimer>

MultilevelQueueWindow::MultilevelQueueWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultilevelQueueWindow)
{
    ui->setupUi(this);

    m_stations = getStations("OTL.txt");

    m_randomEvents = getTasks("random_events.txt");

    table trainLineTable(ui->trainLineTable);
    trainLineTable.setSize(0, 50, {260}, {"Station"});
    trainLineTable.setStations(m_stations);


    table multilevelTable(ui->multilevelTable);
    multilevelTable.setSize(0, 50, {630}, {"Task"});

    ui->worker1_taskLabel->setWordWrap(true);
    ui->worker2_taskLabel->setWordWrap(true);

}

MultilevelQueueWindow::~MultilevelQueueWindow()
{
    delete ui;
}

void MultilevelQueueWindow::takeTaskSetEnabled(bool enabled)
{
    ui->worker1_takeTaskButton->setEnabled(enabled);
    ui->worker2_takeTaskButton->setEnabled(enabled);
}

void MultilevelQueueWindow::clearWorkersTasks()
{
    ui->worker1_taskLabel->setText("");
    ui->worker2_taskLabel->setText("");
}

void MultilevelQueueWindow::enableRandomEvents()
{
    ui->addRandomEventButton->setEnabled(true);
    ui->errorLabel->setText("");
    m_randomEvents = getTasks("random_events.txt");

}

void MultilevelQueueWindow::on_backButton_clicked()
{
    emit backButtonClicked();
}

void MultilevelQueueWindow::on_trainLineTable_itemSelectionChanged()
{
    if (ui->trainLineTable->selectedItems().size() == 0) return;

    QString stName = ui->trainLineTable->selectedItems()[0]->text();

    if (ui->fromSelectionRadioButton->isChecked()) {

        if (m_toSt == stName) return;

        m_fromSt = stName;

        ui->fromStationLabel->setText(m_fromSt);

        ui->toSelectionRadioButton->setChecked(1);

    } else {

        if (m_fromSt == stName) return;

        m_toSt = stName;

        ui->toStationLabel->setText(m_toSt);

    }

    if (ui->fromStationLabel->text() != "" && ui->toStationLabel->text() != "") {

        ui->multilevelNameLabel->setText("Section: " + m_fromSt + " - " + m_toSt);

        takeTaskSetEnabled(true);
        ui->addTaskButton->setEnabled(true);
        enableRandomEvents();
        clearWorkersTasks();

        table multilevelTable(ui->multilevelTable);
        m_mlQ = lineSectToMlQ(getSection(m_stations, m_fromSt, m_toSt));
        multilevelTable.setMlQ(m_mlQ);

    }
}

void MultilevelQueueWindow::on_worker1_takeTaskButton_clicked()
{

    ui->worker1_taskLabel->setText(*m_mlQ.pop());

    table multilevelTable(ui->multilevelTable);
    multilevelTable.setMlQ(m_mlQ);

    if (m_mlQ.isEmpty()) {
        takeTaskSetEnabled(false);
    }

}

void MultilevelQueueWindow::on_worker2_takeTaskButton_clicked()
{

    ui->worker2_taskLabel->setText(*m_mlQ.pop());

    table multilevelTable(ui->multilevelTable);
    multilevelTable.setMlQ(m_mlQ);

    if (m_mlQ.isEmpty()) {
        takeTaskSetEnabled(false);
    }
}

void MultilevelQueueWindow::on_addRandomEventButton_clicked()
{
    if (m_randomEvents.size() == 0) {
       setLabelText(ui->errorLabel, "No random events left!");
       ui->addRandomEventButton->setEnabled(false);
       return;
    }

    takeTaskSetEnabled(true);

    int eventNum = getRandomInt(0, m_randomEvents.size()-1);
    m_mlQ.push(m_randomEvents[eventNum]->title, m_randomEvents[eventNum]->priority);
    table multilevelTable(ui->multilevelTable);
    multilevelTable.setMlQ(m_mlQ);

    m_randomEvents.erase(m_randomEvents.begin() + eventNum);
}

void MultilevelQueueWindow::on_addTaskListButton_clicked()
{

    clearWorkersTasks();
    takeTaskSetEnabled(false);

    table multilevelTable(ui->multilevelTable);

    multilevelTable.clear();
    multilevelTable.setSize(0, 50, {630}, {"Task"});

    QString mlQName = ui->taskListNameInput->text();

    if (mlQName == "") {
        mlQName = "Construction list №" + QString::number(getRandomInt(1000, 9999));
    }

    setLabelText(ui->multilevelNameLabel, mlQName);

    m_mlQ = MultilevelQueue<QString>();

    enableRandomEvents();

    ui->addTaskButton->setEnabled(true);
}

void MultilevelQueueWindow::on_addTaskButton_clicked()
{
    QString taskName = ui->taskNameInput->text();

    if (taskName == "") {
        taskName = "Task №" + QString::number(getRandomInt(1000, 9999));
    }

    uint prior = ui->taskPriorInput->value();

    m_mlQ.push(taskName, prior);

    table multilevelTable(ui->multilevelTable);
    multilevelTable.setMlQ(m_mlQ);

    takeTaskSetEnabled(true);
}

void MultilevelQueueWindow::on_demoButton_clicked()
{
    if (ui->multilevelTable->rowCount() != 0) {

        QMessageBox::StandardButton exit = QMessageBox::question(this, "Start demo mode", "Multilevel queue table is not empty. If you start demo mode, all data will be deleted. Are you sure?",
                                                                 QMessageBox::Yes | QMessageBox::No);

        if (exit == QMessageBox::No) return;

    }

    ui->demoModeLabel->setText("Demonstration mode");

    ui->backButton->setEnabled(false);

    table multilevelTable(ui->multilevelTable);

    multilevelTable.clear();
    multilevelTable.setSize(0, 50, {630}, {"Task"});

    QTimer::singleShot(1000, this, [this]{ui->trainLineTable->selectRow(2);});
    QTimer::singleShot(3000, this, [this]{ui->trainLineTable->selectRow(4);});
    QTimer::singleShot(5000, this, SLOT(on_worker1_takeTaskButton_clicked()));
    QTimer::singleShot(6000, this, SLOT(on_worker1_takeTaskButton_clicked()));
    QTimer::singleShot(7000, this, SLOT(on_worker2_takeTaskButton_clicked()));
    QTimer::singleShot(8000, this, SLOT(on_worker1_takeTaskButton_clicked()));
    QTimer::singleShot(10000, this, [this]{ui->taskListNameInput->setText("Upgrading Faculty of Cybernetics");});
    QTimer::singleShot(12000, this, SLOT(on_addTaskListButton_clicked()));
    QTimer::singleShot(13500, this, [this]{ui->taskPriorInput->setValue(4);});
    QTimer::singleShot(14500, this, [this]{ui->taskNameInput->setText("Throw away all old equipment");});
    QTimer::singleShot(15500, this, SLOT(on_addTaskButton_clicked()));
    QTimer::singleShot(17000, this, [this]{ui->taskPriorInput->setValue(1);});
    QTimer::singleShot(18000, this, [this]{ui->taskNameInput->setText("Say you do not have money because of COVID-19");});
    QTimer::singleShot(19000, this, SLOT(on_addTaskButton_clicked()));
    QTimer::singleShot(21500, this, [this]{ui->taskPriorInput->setValue(2);});
    QTimer::singleShot(22500, this, [this]{ui->taskNameInput->setText("Start outer ellaboration ");});
    QTimer::singleShot(23500, this, SLOT(on_addTaskButton_clicked()));
    QTimer::singleShot(25000, this, [this]{ui->taskPriorInput->setValue(4);});
    QTimer::singleShot(26000, this, [this]{ui->taskNameInput->setText("Install awesome new windows");});
    QTimer::singleShot(27000, this, SLOT(on_addTaskButton_clicked()));
    QTimer::singleShot(29000, this, SLOT(on_worker1_takeTaskButton_clicked()));
    QTimer::singleShot(29300, this, SLOT(on_worker1_takeTaskButton_clicked()));
    QTimer::singleShot(29600, this, SLOT(on_worker1_takeTaskButton_clicked()));
    QTimer::singleShot(29900, this, SLOT(on_worker1_takeTaskButton_clicked()));

    QTimer::singleShot(30000, this, [this]{
        ui->demoModeLabel->setText("");
        ui->backButton->setEnabled(true);
    });
}
