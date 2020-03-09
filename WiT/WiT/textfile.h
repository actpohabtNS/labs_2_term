#ifndef TEXTFILES_H
#define TEXTFILES_H
#include <vector>
#include <fstream>
#include <string>
#include "train.h"


class textFile
{
public:
    textFile(std::string location);

    std::vector<train> getData();

    void addTrain(std::vector<QString> data);

    void removeTrain(std::vector<train>& trains, int trainId);

    void editTrain(std::vector<train>& trains, int oldTrainId, train newTrain);

    void writeTrains(std::vector<train> trains);

private:
    std::string m_location;

};

#endif // TEXTFILES_H
