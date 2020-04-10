#include "train.h"
#include "functs.h"
#include <stdexcept>
#include "random.h"

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

    for (QString info : getInfo())
    {
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

short train::getTrainTypeShort()
{
    if (m_type == "International")
        return 0;
    else if (m_type == "Rapid")
        return 1;
    else if (m_type == "Local")
        return 2;
    else if(m_type == "Suburbal")
        return 3;
    else
    {
        qDebug() << "Unknown train type:" << m_type;
        return -1;
    }
}

short train::getShort(QString field)
{
    if (field == "type")
        return getTrainTypeShort();
    else if (field == "number")
        return m_number;
    else
    {
        qDebug() << "Unknown short field:" << field;
        return -1;
    }
}

bool greaterByField(QString field, train t1, train t2, bool strict)
{
    bool res = false;

    if (field == "id")
    {
        return strict ? t1.getId() > t2.getId() : t1.getId() >= t2.getId();
    }
    else if (field == "number")
    {
        return strict ? t1.getTrainNumber() > t2.getTrainNumber() : t1.getTrainNumber() >= t2.getTrainNumber();
    }
    else if (field == "from")
    {
        return compareQString(t1.getFrom(), t2.getFrom(), strict);
    }
    else if (field == "to")
    {
        return compareQString(t1.getTo(), t2.getTo(), strict);
    }
    else if (field == "arrTime")
    {
        return strict ? t1.getArrTime() > t2.getArrTime() : t1.getArrTime() >= t2.getArrTime();
    }
    else if (field == "depTime")
    {
        return strict ? t1.getDepTime() > t2.getDepTime() : t1.getDepTime() >= t2.getDepTime();
    }
    else if (field == "type")
    {
        return compareQString(t1.getTrainType(), t2.getTrainType(), strict);
    }
    else if (field == "rate")
    {
        return strict ? t1.getTrainRate() > t2.getTrainRate() : t1.getTrainRate() >= t2.getTrainRate();
    }
    else
    {
        throw new std::out_of_range("Wrong field name!");
    }

    return res;
}

bool equalByField(QString field, train t1, train t2)
{
    return !(greaterByField(field, t1, t2, true) == greaterByField(field, t1, t2, false));
}

bool sequenceGreater(std::vector<QString> sortingSequence, train t1, train t2, bool strict)
{
    bool res;
    uint field_idx = 0;

    do {
        res = greaterByField(sortingSequence[field_idx], t1, t2, strict);
        field_idx++;
    } while (field_idx < sortingSequence.size() && equalByField(sortingSequence[field_idx-1], t1, t2));

    return res;
}

bool train::time::operator ==(train::time t)
{
    if (this->getHours() != t.getHours() || this->getMinutes() != t.getMinutes())
        return false;
    else return true;
}

bool train::time::operator >(train::time t)
{
    if (this->getHours() != t.getHours())
    {
        return this->getHours() > t.getHours();
    }
    else if (this->getMinutes() != t.getMinutes())
    {
        return this->getMinutes() > t.getMinutes();
    }
    else return false;
}

bool train::time::operator >=(train::time t)
{
    return (*this == t ? true : *this > t);
}

bool compareQString(QString s1, QString s2, bool strict)
{
    int numComp = QString::localeAwareCompare(s1.toUpper(), s2.toUpper());

    if (strict && numComp > 0)
        return true; //Caution! compare("A", "B") > 0!
    else if (!strict && numComp >= 0)
        return true;
    else return false;
}

short getMinShortByField(QString field, std::vector<train> trains, int first, int last)
{
    if(last == -1) last = trains.size()-1;

    short min = trains[first].getShort(field);

    for (int i = first+1; i <= last; i++)
    {
        if (min > trains[i].getShort(field))
            min = trains[i].getShort(field);
    }

    return min;
}

short getMaxShortByField(QString field, std::vector<train> trains, int first, int last)
{
    if(last == -1) last = trains.size()-1;

    short max = trains[first].getShort(field);

    for (int i = first+1; i <= last; i++)
    {
        if (max < trains[i].getShort(field))
            max = trains[i].getShort(field);
    }

    return max;
}

std::vector<train> *randomize(int size)
{
    std::vector<train>* trains = new std::vector<train>();

    for (int idx = 0; idx < size; idx++)
    {
        train tr;
        tr.randomize();
        trains->push_back(tr);
    }

    return trains;
}
