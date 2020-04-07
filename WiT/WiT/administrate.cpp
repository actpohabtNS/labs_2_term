#include "administrate.h"
#include "ui_administrate.h"
#include "searchoptionswindow.h"
#include "addtrainwindow.h"
#include "sortoptionswindow.h"
#include "table.h"
#include "functs.h"
#include "textfile.h"
#include "binfile.h"
#include "benchmark.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <chrono>
#include <QTimer>


Administrate::Administrate(QWidget *parent, bool demo) :
    QWidget(parent),
    ui(new Ui::Administrate)
{
    ui->setupUi(this);

    m_sOW = new sortoptionswindow(this);
    connect(m_sOW, SIGNAL(sortingApplied(ushort, std::vector<QString>)), this, SLOT(sort(ushort, std::vector<QString>)));

    m_demoMode = demo;

    QString tooltip="Add new train";
    ui->addTrainButton->setToolTip(tooltip);

    table trainTable(ui->trainTable);
    textFile textFile(m_demoMode ? "textfile_demo.txt" : "textfile.txt");
    m_trains = textFile.getData();

    binFile binFile(m_demoMode ? "binfile_demo.bin" : "binfile.bin");
    m_trains_bin = binFile.getData();

    trainTable.setTrainTable(m_trains);

    if (!demo) return;

    ui->pageName_1->setText("Demonstration mode");

    QTimer::singleShot(1500, this, SLOT(on_addTrainButton_clicked_delay()));

    QTimer::singleShot(6000, this, SLOT(searchFieldWrite_delay()));

    QTimer::singleShot(7500, this, SLOT(makeSearchRequest_delay()));


    QTimer::singleShot(18000, this, SLOT(selectRow_delay()));

    QTimer::singleShot(19500, this, SLOT(on_trainEditButton_clicked_delay()));

    QTimer::singleShot(25500, this, SLOT(on_removeTrainButton_clicked_delay()));
}

Administrate::~Administrate()
{
    delete ui;
}

void Administrate::on_pushButton_1_clicked()
{
    emit backButtonClicked();
}

void Administrate::on_trainAdded(train newTrain)
{
    table trainTable(ui->trainTable);

    textFile textFile(m_demoMode ? "textfile_demo.txt" : "textfile.txt");
    textFile.addTrain(newTrain.getInfo());

    binFile binFile(m_demoMode ? "binfile_demo.bin" : "binfile.bin");
    binFile.addTrain(newTrain);

    m_trains_arr.push_back(newTrain);

    m_trains = textFile.getData();

    if (ui->arrayButton->isChecked()) trainTable.setTrainTable(m_trains_arr);
    else trainTable.setTrainTable(m_trains);
}


void Administrate::on_addTrainButton_clicked()
{
    addTrainWindow addTW(this);

    connect(&addTW, SIGNAL(trainAdded(train)), this, SLOT(on_trainAdded(train)));

    addTW.setModal(true);
    addTW.exec();
}

void Administrate::on_addTrainButton_clicked_delay()
{
    addTrainWindow addTW(this, "add", true);

    connect(&addTW, SIGNAL(trainAdded(train)), this, SLOT(on_trainAdded(train)));

    addTW.setModal(true);
    addTW.exec();
}

void Administrate::on_trainEditButton_clicked()
{
    addTrainWindow addTW(this, "edit");
    train train = m_trains[ui->trainTable->selectedItems()[0]->row()];
    addTW.setTrain(train);
    addTW.showTrainData(train);

    connect(&addTW, SIGNAL(trainEdited(train)), this, SLOT(on_trainEdited(train)));

    addTW.setModal(true);
    addTW.exec();
}

void Administrate::on_trainEditButton_clicked_delay()
{
    addTrainWindow addTW(this, "edit", true);

    train train = m_trains[ui->trainTable->selectedItems()[0]->row()];
    addTW.setTrain(train);
    addTW.showTrainData(train);

    connect(&addTW, SIGNAL(trainEdited(train)), this, SLOT(on_trainEdited(train)));

    addTW.setModal(true);
    addTW.exec();
}

void Administrate::on_removeTrainButton_clicked_delay()
{
    on_removeTrainButton_clicked(true);
}


void Administrate::on_trainEdited(train newTrain)
{
    textFile textFile(m_demoMode ? "textfile_demo.txt" : "textfile.txt");
    textFile.editTrain(m_trains, newTrain.getId(), newTrain);

    binFile binFile(m_demoMode ? "binfile_demo.bin" : "binfile.bin");
    binFile.editTrain(m_trains_bin, newTrain.getId(), newTrain);

    editTrain(m_trains_arr, newTrain.getId(), newTrain);

    table trainTable(ui->trainTable);

    if (ui->arrayButton->isChecked()) trainTable.setTrainTable(m_trains_arr);
    else trainTable.setTrainTable(m_trains);
}

void Administrate::saveSettings(std::vector<bool> settings)
{
    m_searchSettings = settings;
}

void Administrate::changeSearchField(QString newRequest)
{
    QStringList timeIntervals = newRequest.split("-");

    train::time depTime = {stos(timeIntervals[0].split(":")[0].toLocal8Bit().constData()), stos(timeIntervals[0].split(":")[1].toLocal8Bit().constData())};
    train::time arrTime = {stos(timeIntervals[1].split(":")[0].toLocal8Bit().constData()), stos(timeIntervals[1].split(":")[1].toLocal8Bit().constData())};

    ui->searchField->setText(depTime.getTime() + " - " + arrTime.getTime());
    m_searchSettings[0] = true;

    table table(ui->trainTable);
    table.searchTable(m_trains, depTime.getTime() + "-" + arrTime.getTime(), m_searchSettings);
}

void Administrate::sort(ushort sortingAlg, std::vector<QString> sortingSequence)
{
    qDebug() << "SortingAlg:" << sortingAlg;

    for (QString elem : sortingSequence)
    {
        qDebug() << elem;
    }
}

void Administrate::on_optionsButton_clicked()
{
    searchOptionsWindow searchOW;
    searchOW.showSettings(m_searchSettings);

    connect(&searchOW, SIGNAL(searchSettingApplied(std::vector<bool>)), this, SLOT(saveSettings(std::vector<bool>)));
    connect(&searchOW, SIGNAL(changeSearchField(QString)), this, SLOT(changeSearchField(QString)));

    searchOW.setModal(true);
    searchOW.exec();
}

void Administrate::on_searchField_returnPressed()
{
    QString request = ui->searchField->text().replace(" ", "");

    if (getIntervalMask(request) != "") m_searchSettings = {true};

    table trainTable(ui->trainTable);
    std::vector<train> searchedTrains;

    if (ui->arrayButton->isChecked())
    {
        searchedTrains = searchTrains(m_trains_arr, ui->searchField->text(), m_searchSettings);
    }
    else
    {
        searchedTrains = searchTrains(m_trains, ui->searchField->text(), m_searchSettings);
    }

    trainTable.setTrainTable(searchedTrains);
}

void Administrate::on_clearSearchButton_clicked()
{
    ui->searchField->setText("");
    table trainTable(ui->trainTable);

    if (ui->arrayButton->isChecked()) trainTable.setTrainTable(m_trains_arr);
    else trainTable.setTrainTable(m_trains);
}

void Administrate::on_trainTable_itemSelectionChanged()
{
    if (ui->trainTable->selectedItems().size() == 0 || ui->trainTable->columnCount() == 1)
    {
        ui->trainEditButton->setEnabled(false);
        ui->removeTrainButton->setEnabled(false);
    }
    else
    {
        ui->trainEditButton->setEnabled(true);
        ui->removeTrainButton->setEnabled(true);
    }
}

void Administrate::on_removeTrainButton_clicked(bool demo)
{
    if (!demo)
    {
        QMessageBox::StandardButton deleteTrain = QMessageBox::question(this, "Delete train", "Are you sure?",
                                                                 QMessageBox::Yes | QMessageBox::No);
        if (deleteTrain == QMessageBox::No) return;
    }

    table trainTable(ui->trainTable);

    textFile textFile(m_demoMode ? "textfile_demo.txt" : "textfile.txt");
    textFile.removeTrain(m_trains, (ui->trainTable->item(ui->trainTable->selectedItems()[0]->row(), 0)->text()).toInt());

    binFile binFile(m_demoMode ? "binfile_demo.bin" : "binfile.bin");
    binFile.removeTrain(m_trains_bin, (ui->trainTable->item(ui->trainTable->selectedItems()[0]->row(), 0)->text()).toInt());

    removeTrain(m_trains_arr, (ui->trainTable->item(ui->trainTable->selectedItems()[0]->row(), 0)->text()).toInt());

    if (ui->arrayButton->isChecked()) trainTable.setTrainTable(m_trains_arr);
    else trainTable.setTrainTable(m_trains);
}



void Administrate::on_textFileButton_clicked(bool checked)
{
    if (!checked) return;

    table trainTable(ui->trainTable);
    trainTable.setTrainTable(m_trains);
}

void Administrate::on_arrayButton_clicked(bool checked)
{
    if (!checked) return;

    table trainTable(ui->trainTable);
    trainTable.setTrainTable(m_trains_arr);
}

void Administrate::on_searchField_textChanged(QString)
{
    QString mode = getIntervalMask(ui->searchField->text());

    if (mode != "")
    {
        ui->intervalLabel->setText("[ " + mode + " ] interval mask");

    } else ui->intervalLabel->setText("");
}

void Administrate::searchFieldWrite_delay()
{
    ui->searchField->setText("Kyiv");
}

void Administrate::makeSearchRequest_delay()
{
    QTimer::singleShot(0, this, SLOT(on_searchField_returnPressed()));
    QTimer::singleShot(3000, this, SLOT(on_optionsButton_clicked_delay()));

    QTimer::singleShot(7000, this, SLOT(on_searchField_returnPressed()));
    QTimer::singleShot(9000, this, SLOT(on_clearSearchButton_clicked()));
}

void Administrate::on_optionsButton_clicked_delay()
{
    searchOptionsWindow searchOW(this, true);
    searchOW.showSettings(m_searchSettings);

    connect(&searchOW, SIGNAL(searchSettingApplied(std::vector<bool>)), this, SLOT(saveSettings(std::vector<bool>)));

    searchOW.setModal(true);
    searchOW.exec();
}

void Administrate::selectRow_delay()
{
    ui->trainTable->selectRow(4);
}

void Administrate::on_sortingButton_clicked()
{        
    m_sOW->setModal(true);
    m_sOW->exec();
}
