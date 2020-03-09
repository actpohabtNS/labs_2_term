#ifndef FUNCTS_H
#define FUNCTS_H
#include <vector>
#include <QString>
#include <fstream>
#include "circularlinkedlist.h"
#include "station.h"

std::vector<Station*> getStations(QString filepath);

int getRandomInt(int min, int max);

void updateRandomSeed();

#endif // FUNCTS_H
