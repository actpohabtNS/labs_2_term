#include "train.h"
#include "functs.h"

train::train(int id, short number, QString from, QString to, QString type, time depTime, time arrTime, double rate)
{
       m_id = id;
       m_number = number;
       m_from = from;
       m_to = to;
       m_type = type;
       m_depTime = depTime;
       m_arrTime = arrTime;
       m_rate = rate;
}



int train::getId()
{
    return m_id;
}

short train::getTrainNumber()
{
    return m_number;
}

QString train::getFrom()
{
    return m_from;
}

QString train::getTo()
{
    return m_to;
}

QString train::getTrainType()
{
    return m_type;
}

train::time train::getDepTime()
{
    return m_depTime;
}

train::time train::getArrTime()
{
    return m_arrTime;
}

double train::getTrainRate()
{
    return m_rate;
}



std::vector<QString> train::getInfo()
{
    return std::vector<QString> {QString::number(m_id), QString::number(m_number), m_from, m_to, m_type, m_depTime.getTime(), m_arrTime.getTime(), QString::number(m_rate)};
}

QString train::getInfoQStr()
{
    QString res = "";

    for (QString info : getInfo()){
        res += info + " ";
    }

    return res;
}

void train::randomize()
{

    m_id = getRandomInt(10000000, 99999999);
    m_number = getRandomInt(1000, 9999);

    m_from = TRAIN_CITIES[getRandomInt(0, TRAIN_CITIES.size()-1)];
    m_to = TRAIN_CITIES[getRandomInt(0, TRAIN_CITIES.size()-1)];

    m_type = TRAIN_TYPES[getRandomInt(0, TRAIN_TYPES.size()-1)];

    m_arrTime = {getRandomShort(0, 22), getRandomShort(0, 59)};
    m_depTime = {getRandomShort(0, 22), getRandomShort(0, 59)};

    m_rate = static_cast<double>(getRandomInt(0, 10)) / 10;

}

