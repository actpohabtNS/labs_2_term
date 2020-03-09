#include <QDebug>
#include <ctime>
#include <windows.h>
#include "addtrainwindow.h"
#include "ui_addtrainwindow.h"
#include "textfile.h"
#include "binfile.h"
#include <QTime>
#include <QTimer>


addTrainWindow::addTrainWindow(QWidget *parent, QString mode, bool test) :
    QDialog(parent),
    ui(new Ui::addTrainWindow)
{

    ui->setupUi(this);

    m_mode = mode;

    if (m_mode == "edit") {

        ui->pageName->setText("Edit train");
        ui->applyAddTrainButton->setText("Apply changes");

    }

    if (!test) return;

    if (mode == "add") {

        QTimer::singleShot(1500, this, SLOT(showTrain_delay()));

    } else if (mode == "edit") {

        QTimer::singleShot(1500, this, SLOT(changeTrainTo_delay()));
    }

    QTimer::singleShot(3000, this, SLOT(on_applyAddTrainButton_clicked()));

}


addTrainWindow::~addTrainWindow()
{
    delete ui;
}

void addTrainWindow::on_applyAddTrainButton_clicked()
{

    if (m_mode == "add") {


        train newTrain = getTrainFromForm();
        emit trainAdded(newTrain);

    } else if (m_mode == "edit") {

        train newTrain = getTrainFromForm(m_train.getId());
        emit trainEdited(newTrain);

    }


    close();

}

void addTrainWindow::on_cancelButton_clicked()
{
    close();
}

void addTrainWindow::showTrain_delay()
{
    SYSTEMTIME st;
    srand(static_cast<unsigned int>(time(0) + st.wMilliseconds * 100000));

    train randomTrain;
    randomTrain.randomize();

    showTrainData(randomTrain);
}

void addTrainWindow::changeTrainTo_delay()
{
    ui->toInput->setText("Odesa");
}

train addTrainWindow::getTrainFromForm(int id)
{
    int trainNumber = ui->trainNumberInput->text().toInt();

    if (!id) {
        srand(trainNumber);
        id = getRandomInt(10000000, 99999999);
    }

    QString from = ui->fromInput->text();
    QString to = ui->toInput->text();
    QString trainType = ui->trainTypeInput->currentText();
    train::time depTime = {(short)ui->departureTimeInput->time().hour(), (short)ui->departureTimeInput->time().minute()};
    train::time arrTime = {(short)ui->arrivalTimeInput->time().hour(), (short)ui->arrivalTimeInput->time().minute()};
    double trainRate = ui->trainRateInput->value();

    train train(id, trainNumber, from, to, trainType, depTime, arrTime, trainRate);
    return train;
}

void addTrainWindow::showTrainData(train train)
{

    std::vector<QString> trainData = train.getInfo();

    ui->trainNumberInput->setText(trainData[1]);
    ui->fromInput->setText(trainData[2]);
    ui->toInput->setText(trainData[3]);

    int index = ui->trainTypeInput->findText(trainData[4]);
    ui->trainTypeInput->setCurrentIndex(index);

    QTime depTime(trainData[5].split(":")[0].toInt(), trainData[5].split(":")[1].toInt());
    ui->departureTimeInput->setTime(depTime);

    QTime arrTime(trainData[6].split(":")[0].toInt(), trainData[6].split(":")[1].toInt());
    ui->arrivalTimeInput->setTime(arrTime);

    ui->trainRateInput->setValue(trainData[7].toDouble());
}

void addTrainWindow::setTrain(train train)
{
    m_train = train;
}
