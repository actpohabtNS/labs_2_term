#ifndef BINFILE_H
#define BINFILE_H

#include "train.h"
#include "functs.h"
#include <QtDebug>
#include <vector>
#include <fstream>

class binFile
{
public:
    binFile(std::string location);

    void addTrain(train train);

    std::vector<train> getData();

    void writeTrains(std::vector<train> trains);

    void removeTrain(std::vector<train>& trains, int trainId);

    void editTrain(std::vector<train>& trains, int oldTrainId, train newTrain);

private:
    std::string m_location;
};

#endif // BINFILE_H
