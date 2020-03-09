#ifndef FUNCTS_H
#define FUNCTS_H

#include "train.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <QString>

std::vector<std::string> split(std::string str, std::string del);

short stos(std::string s);

void toCharArr(char *array, QString string);

void removeTrain(std::vector<train>& trains, int trainId);

void editTrain(std::vector<train> &trains, int oldTrainId, train newTrain);

std::vector<train> searchTrains(std::vector<train> trains, QString request, std::vector<bool> settings);

int getRandomInt(int min, int max);

short getRandomShort(short min, short max);

double getRandomDouble(double min, double max);

QString getIntervalMask(QString request);

#endif // FUNCTS_H
