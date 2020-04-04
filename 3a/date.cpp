#include "date.h"
#include "functs.h"
#include <stdexcept>
#include <QDebug>

Date::Date()
{
    this->day = 1;
    this->month = 1;
    this->year = 0;
}

Date::Date(int day, int month, int year)
{
    this->year = year;
    this->month = month;
    this->day = day;

    correct();
}

bool Date::operator ==(Date d)
{
    if (year != d.year || month != d.month || day != d.day)
        {
            return false;
    } else return true;
}

bool Date::operator >(Date d)
{
    if (year != d.year) {
            return year > d.year;
        } else if (month != d.month) {
            return month > d.month;
        } else if (day != d.day) {
            return day > d.day;
    } else return false;
}

bool Date::operator >=(Date d)
{
    return (*this == d ? true : *this > d);
}

bool Date::operator <(Date d)
{
    return !(*this >= d);
}

bool Date::operator <=(Date d)
{
    return (*this == d ? true : *this < d);
}

void Date::randomize()
{
    day = getRandomInt(1, 31);
    month = getRandomInt(1, 12);
    year = getRandomInt(1000, 3000);

    correct();
}

void Date::correct()
{
    if (month < 1) month = 1;
    if (day < 1) day = 1;

    int monthShift = 0;

    if (year % 4 == 0 && month == 2 && day > 29)
    {
        monthShift = day / 29;
        day %= 29;
    }
    else if (year % 4 != 0 && month == 2 && day > 28)
    {
        monthShift = day / 28;
        day %= 28;
    }
    else if (month <= 7)
    {
        if (month % 2 == 1)
        {
            monthShift = cutDay(day, 31);
        }
        else
        {
            monthShift = cutDay(day, 30);
        }
    } else
    {
        if (month % 2 == 1)
        {
            monthShift = cutDay(day, 30);
        }
        else
        {
            monthShift = cutDay(day, 31);
        }
    }

    month += monthShift;

    if (month > 12)
    {
        int yearShift = month / 12;
        year += yearShift;
        month %= 12;
    }
}

Date::operator QString()
{
    return (toISOtime(day) + "." + toISOtime(month) + " " + QString::number(year));
}

Date *getRandomDateArray(unsigned int size)
{
    if (size < 1) throw std::range_error("Size of array must be > 0");

    Date* arr = new Date[size];

    for (unsigned int i = 0; i < size; i++)
    {
        Date d;
        d.randomize();
        arr[i] = d;
    }

    return arr;
}

int cutDay(int& day, int max)
{
    int shift = 0;
    if (day > max)
    {
        shift = day / max;
        day %= max;
    }
    return shift;
}

QString toISOtime(int timeUnit)
{
    if (timeUnit < 10) return ("0" + QString::number(timeUnit));
    return QString::number(timeUnit);
}
