#include "functs.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <windows.h>
#include <chrono>

std::vector<Station*> getStations(QString filepath)
{

    QFile file(filepath);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "[ ERROR ] failed to open file " << filepath;
        return {};
    }

    std::vector<Station*> stations;

    QString stationQstr;
    QStringList stationData;

    QTextStream stream(&file);

    while (!stream.atEnd()) {
        stationQstr = file.readLine();

        stationData = stationQstr.split(",");

        stations.push_back(new Station{stationData[0], stationData[1].toDouble()});
    }


    return stations;
}

int getRandomInt(int min, int max)
{

    updateRandomSeed();

    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void updateRandomSeed()
{
    auto time = std::chrono::high_resolution_clock::now().time_since_epoch();

    srand(static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::microseconds>(time).count()));
}
