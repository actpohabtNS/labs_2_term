#include "binfile.h"


binFile::binFile(std::string location)
{
    m_location = location;
}

void binFile::addTrain(train newTrain)
{
    std::fstream binFile;
    binFile.open(m_location, std::ios_base::app| std::ios_base::binary);

    if (!binFile.is_open()) {
        qDebug() << "FAILED to open binfile (writing)" << QString::fromStdString(m_location);
        return;
    }

    //binFile.write((char*)&newTrain, sizeof (train)); <- that was obvious, but not working while reading

    auto start = std::chrono::high_resolution_clock::now();

    int id = newTrain.getId();
    short trainNumber = newTrain.getTrainNumber();


    char from[30], to[30], trainType[30];          //
    toCharArr(from, newTrain.getFrom());           //
    toCharArr(to, newTrain.getTo());               // That is necessary
    toCharArr(trainType, newTrain.getTrainType()); //

    train::time depTime = newTrain.getDepTime(), arrTime = newTrain.getArrTime();

    double trainRate = newTrain.getTrainRate();

    auto stamp1 = std::chrono::high_resolution_clock::now();

    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stamp1 - start);

    qDebug() << duration1.count();

    binFile.write(reinterpret_cast<char *>(&id), sizeof(id));
    binFile.write(reinterpret_cast<char *>(&trainNumber), sizeof(trainNumber));
    binFile.write(from, sizeof(from));
    binFile.write(to, sizeof(to));
    binFile.write(trainType, sizeof(trainType));
    binFile.write(reinterpret_cast<char *>(&depTime), sizeof(depTime));
    binFile.write(reinterpret_cast<char *>(&arrTime), sizeof(arrTime));
    binFile.write(reinterpret_cast<char *>(&trainRate), sizeof(trainRate));

    auto stamp2 = std::chrono::high_resolution_clock::now();

    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stamp2 - stamp1);

    qDebug() << duration2.count();

    binFile.close();
}

std::vector<train> binFile::getData()
{
    std::fstream binFile;
    binFile.open(m_location, std::ios_base::in | std::ios_base::ate | std::ios_base::binary);

    if (!binFile.is_open()) {
        qDebug() << "FAILED to open binfile (reading)" << QString::fromStdString(m_location);
        return {};
    }

    std::vector<train> trains = {};

    unsigned long int fileSize = binFile.tellg();
    binFile.seekg(0, binFile.beg);
    unsigned long int pos = binFile.tellg();

    while(pos < fileSize) {

        int id;
        short trainNumber;
        char from[30], to[30], trainType[30];
        train::time depTime, arrTime;
        double trainRate;

        binFile.read(reinterpret_cast<char *>(&id), sizeof(id));

        binFile.read(reinterpret_cast<char *>(&trainNumber), sizeof(trainNumber));
        binFile.read(from, sizeof(from));
        binFile.read(to, sizeof(to));
        binFile.read(trainType, sizeof(trainType));
        binFile.read(reinterpret_cast<char *>(&depTime), sizeof(depTime));
        binFile.read(reinterpret_cast<char *>(&arrTime), sizeof(arrTime));
        binFile.read(reinterpret_cast<char *>(&trainRate), sizeof(trainRate));

        QString fromQ(from), toQ(to), trainTypeQ(trainType);

        train trainRead(id, trainNumber, fromQ, toQ, trainTypeQ, depTime, arrTime, trainRate);

        trains.push_back(trainRead);

        pos = binFile.tellg();
    }

    binFile.close();

    return trains;
}

void binFile::writeTrains(std::vector<train> trains)
{
    std::fstream file;
    file.open(m_location, std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);

    if (!file.is_open()) {
        qDebug() << "FAILED to open binfile (rewriting)" << QString::fromStdString(m_location);
        return;
    }

    for (train train : trains) {
        addTrain(train);
    }

    file.close();
}

void binFile::removeTrain(std::vector<train> &trains, int trainId)
{
    for (unsigned int i = 0; i < trains.size(); i++) {
        if (trainId == trains[i].getId()) trains.erase(trains.begin() + i, trains.begin() + i+1);
    }

    writeTrains(trains);
}

void binFile::editTrain(std::vector<train> &trains, int oldTrainId, train newTrain)
{
    for (unsigned int i = 0; i < trains.size(); i++) {
        if (oldTrainId == trains[i].getId()) trains[i] = newTrain;
    }

    writeTrains(trains);
}
