#include "station.h"
#include "functs.h"

Station::Station()
{
    this->name = "";
    this->timeNext = 0;
}

Station::Station(QString name, double timeNext)
{
    this->name = name;
    this->timeNext = timeNext;
}

void Station::randomize()
{
    name = QString::number(getRandomInt(0, 5000000));
    timeNext = static_cast<double>(getRandomInt(10, 100)) / 10;
}
