#ifndef STATION_H
#define STATION_H
#include <QString>

class Station
{
public:
    Station();
    Station(QString name, double timeNext);

    void randomize();


    QString name;
    double timeNext;
};

#endif // STATION_H
