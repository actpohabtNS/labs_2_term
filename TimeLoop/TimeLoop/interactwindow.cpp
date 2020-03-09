#include "interactwindow.h"
#include "ui_interactwindow.h"
#include "circularlinkedlist.h"
#include "functs.h"
#include "table.h"
#include <windows.h>
#include <QtDebug>
#include <chrono>
#include <QTimer>

interactWindow::interactWindow(QWidget *parent, bool demo) :
    QWidget(parent),
    ui(new Ui::interactWindow)
{
    ui->setupUi(this);

    m_demoMode = demo;

    m_table = new table(ui->trainLineTable);
    m_table->setSize(0, 60, {450}, {"Station name"});

    updateRandomSeed();

    if (!demo) return;

    setGoBackEnabled(false);

    ui->pageNameLabel->setText("Demonstration mode");

    QTimer::singleShot(500, this, SLOT(on_loadKUTButton_clicked()));
    QTimer::singleShot(2000, this, [this]{selectRow(2);});
    QTimer::singleShot(3500, this, [this]{selectRow(8);});

    QTimer::singleShot(5000, this, [this]{setTextInput(ui->lineNameInput, "My line");});
    QTimer::singleShot(6500, this, SLOT(on_addLineButton_clicked()));

    QTimer::singleShot(8000, this, SLOT(on_addStButton_clicked()));
    QTimer::singleShot(8200, this, SLOT(on_addStButton_clicked()));
    QTimer::singleShot(8400, this, SLOT(on_addStButton_clicked()));
    QTimer::singleShot(8600, this, SLOT(on_addStButton_clicked()));
    QTimer::singleShot(8800, this, SLOT(on_addStButton_clicked()));
    QTimer::singleShot(9000, this, SLOT(on_addStButton_clicked()));

    QTimer::singleShot(10500, this, [this]{selectRow(0);});
    QTimer::singleShot(12000, this, [this]{selectRow(3);});

    QTimer::singleShot(14500, this, SLOT(on_removeStButton_clicked()));
    QTimer::singleShot(16000, this, SLOT(on_changeStButton_clicked()));

    QTimer::singleShot(16000, this, [this]{setGoBackEnabled(true);});

}

interactWindow::~interactWindow()
{
    delete ui;
}

void interactWindow::clearFromToStations()
{
    ui->fromSelectionRadioButton->setChecked(1);

    ui->fromStationLabel->setText("");
    ui->toStationLabel->setText("");

    m_fromSt = "";
    m_toSt = "";

    ui->timeOutLabel->setText("");
}

void interactWindow::loadLineUI(QString lineName)
{
    ui->trainLineNameLabel->setText(lineName);

    ui->fromSelectionRadioButton->setChecked(1);

    clearFromToStations();

    ui->trainLineTable->clearSelection();
}

void interactWindow::enableButtonsEditingLine(bool enable)
{
    ui->addStButton->setEnabled(enable);
    ui->removeStButton->setEnabled(enable);
    ui->changeStButton->setEnabled(enable);
}

QString interactWindow::generateUniqueStName(QString userStName = "", QString strBeforeNumber = "Station №")
{
    QString stName;

    while (true) {

        stName = (userStName == "") ? strBeforeNumber + QString::number(getRandomInt(1111, 9999)) : userStName;

        if (m_cll.containsStName(stName)) {

            ui->errorLabel->setText("Station with name \"" + stName + "\" already exists!");
            return "";

        } else break;

    }

    ui->errorLabel->setText("");

    return stName;
}

void interactWindow::on_backButton_clicked()
{
    emit backButtonClicked();
}

void interactWindow::on_loadKUTButton_clicked()
{

    CircularLinkedList KUT(getStations("KUT.txt"));

    m_cll = KUT;

    loadLineUI("Kyiv Urban Train");
    m_table->setCLL(m_cll);

    enableButtonsEditingLine(true);
}

void interactWindow::on_loadMCCButton_clicked()
{

    CircularLinkedList MCC(getStations("MCC.txt"));

    m_cll = MCC;

    loadLineUI("Moscow Central Circle");
    m_table->setCLL(m_cll);

    enableButtonsEditingLine(true);
}

void interactWindow::on_loadMMCButton_clicked()
{

    CircularLinkedList MMC(getStations("MMC.txt"));

    m_cll = MMC;

    loadLineUI("Moscow Metro Circle");
    m_table->setCLL(m_cll);

    enableButtonsEditingLine(true);
}

void interactWindow::on_trainLineTable_itemSelectionChanged()
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

        ui->timeOutLabel->setText(QString::number(m_cll.getTime(m_fromSt, m_toSt)));

    }
}

void interactWindow::on_addLineButton_clicked()
{
    m_cll = CircularLinkedList();

    clearFromToStations();

    ui->trainLineTable->setRowCount(0);

    m_table->setCLL(m_cll);

    if (ui->lineNameInput->text() == "") {

        ui->trainLineNameLabel->setText("Line №" + QString::number(getRandomInt(1111, 9999)));

    } else {

        ui->trainLineNameLabel->setText(ui->lineNameInput->text());

    }

    enableButtonsEditingLine(true);

}

void interactWindow::on_addStButton_clicked()
{

    QString stName = generateUniqueStName(ui->addStNameInput->text(), "Station №");
    if (stName == "") return;

    double timeNext = (ui->addStTimeNextInput->value() == 0) ? static_cast<double>(getRandomInt(10, 100))/10 : ui->addStTimeNextInput->value();
    int k = (ui->trainLineTable->selectedItems().size() == 0) ? 1 : ui->trainLineTable->selectedItems()[0]->row() + 1;

    m_cll.insert(k, new Station{stName, timeNext});

    m_table->setCLL(m_cll);

    clearFromToStations();

}

void interactWindow::on_removeStButton_clicked()
{

    int k = (ui->trainLineTable->selectedItems().size() == 0) ? 1 : ui->trainLineTable->selectedItems()[0]->row() + 1;

    m_cll.remove(k);

    m_table->setCLL(m_cll);

    clearFromToStations();

}



void interactWindow::on_changeStButton_clicked()
{

    QString newStName = generateUniqueStName(ui->changeStNameInput->text(), "New Station №");
    if (newStName == "") return;

    int k = (ui->trainLineTable->selectedItems().size() == 0) ? 1 : ui->trainLineTable->selectedItems()[0]->row() + 1;

    m_cll.changeStation(k, new Station{newStName, m_cll.get(k)->timeNext});

    m_table->setCLL(m_cll);

    clearFromToStations();

}

void interactWindow::selectRow(int row)
{
    ui->trainLineTable->selectRow(row);
}

void interactWindow::setTextInput(QLineEdit* input, QString text)
{
    input->setText(text);
}

void interactWindow::setGoBackEnabled(bool enabled)
{
    ui->backButton->setEnabled(enabled);
}
