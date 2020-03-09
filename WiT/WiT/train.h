#ifndef TRAIN_H
#define TRAIN_H
#include <QString>
#include <QDebug>
#include <vector>


const std::vector<QString> TRAIN_TYPES = {"International", "Rapid", "Local", "Suburbal"};
const std::vector<QString> TRAIN_CITIES = {"Vinnytsia", "Dnipro", "Donetsk", "Zhytomyr", "Zaporizhya", "IvanoFrankivsk", "Kyiv", "Kropyvnytskyi", "Luhansk", "Lutsk", "Lviv", "Mykolaiv", "Odesa", "Poltava", "Ryvne", "Sumy", "Ternopyl", "Uzhorod", "Kharkiv", "Kherson", "Khmelnytskyi", "Cherkasy", "Chernyvtsy", "Chernyhiv", "Vyden", "Monako", "Berlin", "Paris", "Rome", "Madrid", "London", "Kopenhahen", "Oslo", "Minsk", "Praha", "Moscow"};

class train
{
public:
    struct time {
        short hours;
        short minutes;

        short getHours() {
            return this->hours;
        }

        short getMinutes() {
            return this->minutes;
        }

        QString getTime() {
            QString s_hours = QString::number(hours), s_minutes = QString::number(minutes);

            if (this->minutes < 10) s_minutes = "0" + s_minutes;
            if (this->hours < 10) s_hours = "0" + s_hours;

            return s_hours + ":" + s_minutes;
        }
    };    

    time m_depTime;
    time m_arrTime;

    train(int id = 0, short number = 0, QString from = "NULL", QString to = "NULL", QString type = "local", time depTime = {0,0}, time arrTime = {0,0}, double rate = 0.5);

    int getId();

    short getTrainNumber();

    QString getFrom();

    QString getTo();

    QString getTrainType();

    time getDepTime();

    time getArrTime();

    double getTrainRate();

    std::vector<QString> getInfo();

    QString getInfoQStr();

    void randomize();

private:
    int m_id;
    short m_number;
    QString m_from;
    QString m_to;
    QString m_type;
    double m_rate;


};

#endif // TRAIN_H
