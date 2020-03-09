#include "functs.h"
#include <string>
#include <vector>
#include <limits>
#include <stdexcept>
#include <QDebug>

std::vector<std::string> split(std::string str, std::string del) {
    std::vector<std::string> res;
    int pos1 = 0, pos2 = 0;


    while (true) {
        pos2 = str.find(del, pos2);

        if (pos2 == std::string::npos) {
            if (str.length() != pos1) res.push_back(str.substr(pos1));
            break;
        }
        std::string substr;
        res.push_back(str.substr(pos1, pos2 - pos1));
        pos1 = pos2 + del.length();
        pos2 += del.length();
    }

    return res;
}

short stos(std::string s)
{
    int res = stoi(s);

    if (res < std::numeric_limits<short>::min() || res > std::numeric_limits<short>::max()) {
        throw std::range_error("short out of range");
    }

    return res;
}

void toCharArr(char *array, QString string)
{
    int i = 0;
   for(; i < string.length(); i++) {
       if (!string.at(i).isLetter()) return;
       array[i] = string.at(i).toLatin1();
   }

   array[i] = '\0';

}

void removeTrain(std::vector<train> &trains, int trainId)
{
    for (unsigned int i = 0; i < trains.size(); i++) {
        if (trainId == trains[i].getId()) trains.erase(trains.begin() + i, trains.begin() + i+1);
    }

}

void editTrain(std::vector<train> &trains, int oldTrainId, train newTrain)
{
    for (unsigned int i = 0; i < trains.size(); i++) {
        if (oldTrainId == trains[i].getId()) trains[i] = newTrain;
    }
}

int getRandomInt(int min, int max)
{

    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

short getRandomShort(short min, short max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

    return static_cast<short>(rand() * fraction * (max - min + 1) + min);
}

std::vector<train> searchTrains(std::vector<train> trains, QString search, std::vector<bool> settings)
{
    std::vector<train> resultTrains = {};

    if (settings[0]) {

        QString intervalMode = getIntervalMask(search);


        QStringList intervals = search.split("-");

        train::time depTime, arrTime;
        int fromNum = 0, toNum = 0;
        double fromRate = 0, toRate = 0;

        if (intervalMode == "Time") {

            depTime = {stos(intervals[0].split(":")[0].toLocal8Bit().constData()), stos(intervals[0].split(":")[1].toLocal8Bit().constData())};
            arrTime = {stos(intervals[1].split(":")[0].toLocal8Bit().constData()), stos(intervals[1].split(":")[1].toLocal8Bit().constData())};

        } else if (intervalMode == "Number") {

            fromNum = intervals[0].toInt();
            toNum = intervals[1].toUInt();

        } else if (intervalMode == "Rate") {

            fromRate = intervals[0].toDouble();
            toRate = intervals[1].toDouble();

        }


        for (train train : trains) {
            bool suits = false;


            if (intervalMode == "Time") {

                if (train.getDepTime().getTime() >= depTime.getTime() && train.getArrTime().getTime() <= arrTime.getTime()) {
                    suits = true;
                }

            } else if (intervalMode == "Number") {

                if (train.getTrainNumber() >= fromNum && train.getTrainNumber() <= toNum) {
                    suits = true;
                }

            } else if (intervalMode == "Rate") {

                if (train.getTrainRate() >= fromRate && train.getTrainRate() <= toRate) {
                    suits = true;
                }

            }

            if (suits) resultTrains.push_back(train);

        }

    } else {


        for (train train : trains) {

            for (int propNum = 0; propNum < 8; propNum++) {

                if (settings[propNum+1] && train.getInfo()[propNum].toLower().contains(search.toLower())) {
                    resultTrains.push_back(train);
                }

            }

        }


    }

    return resultTrains;
}

QString getIntervalMask(QString request)
{
    request.replace(" ", "");

    if (request.contains(QRegExp("[0-2][0-9]:[0-5][0-9]-[0-2][0-9]:[0-5][0-9]"))) return "Time";

    else if (request.contains(QRegExp("[1-9][0-9][0-9][0-9]-[1-9][0-9][0-9][0-9]"))) return "Number";

    else if (request.contains(QRegExp("[0-1].[0-9]-[0-1].[0-9]"))) return "Rate";

    else return "";

}
