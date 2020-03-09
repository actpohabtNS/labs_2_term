#include <QDebug>
#include "textfile.h"
#include "functs.h"
#include "train.h"


textFile::textFile(std::string location)
{
    m_location = location;
}

std::vector<train> textFile::getData()
{
    std::vector<train> trains;

    std::fstream file(m_location);

    if (!file.is_open()) {
        qDebug() << "FAILED to open file (reading)" << QString::fromStdString(m_location);
    }

    std::string s_line;

    while (std::getline(file, s_line)) {

        if (s_line == "") break;

        std::vector<std::string> line = split(s_line, " ");
        std::vector<std::string> depTime = split(line[5], ":");
        std::vector<std::string> arrTime = split(line[6], ":");

        train train {std::stoi(line[0]), stos(line[1]), QString::fromStdString(line[2]),
                    QString::fromStdString(line[3]), QString::fromStdString(line[4]),
                    train::time{stos(depTime[0]), stos(depTime[1])}, train::time{stos(arrTime[0]), stos(arrTime[1])}, std::stod(line[7])};

        trains.push_back(train);

    }

    file.close();

    return trains;
}

void textFile::addTrain(std::vector<QString> data)
{
    std::fstream file;

    file.open(m_location, std::ios::app);

    if (!file.is_open()) {
        qDebug() << "FAILED to open textfile (writing)" << QString::fromStdString(m_location);
        return;
    }


    for (QString str : data) {
        file << str.toLocal8Bit().constData() << " ";
    }

    file << "\n";

    file.close();
}

void textFile::writeTrains(std::vector<train> trains)
{
     std::fstream file;
     file.open(m_location, std::ios_base::out | std::ios_base::trunc);

     if (!file.is_open()) {
         qDebug() << "FAILED to open file (rewriting)" << QString::fromStdString(m_location);
         return;
     }

     for (train train : trains) {
         file << train.getInfoQStr().toLocal8Bit().constData();
         file << "\n";
     }

     file.close();
}


void textFile::removeTrain(std::vector<train>& trains, int trainId)
{
    for (unsigned int i = 0; i < trains.size(); i++) {
        if (trainId == trains[i].getId()) trains.erase(trains.begin() + i, trains.begin() + i+1);
    }

    writeTrains(trains);
}

void textFile::editTrain(std::vector<train> &trains, int oldTrainId, train newTrain)
{
    for (unsigned int i = 0; i < trains.size(); i++) {
        if (oldTrainId == trains[i].getId()) trains[i] = newTrain;
    }

    writeTrains(trains);
}
