#include "date.h"
#include "functs.h"
#include <stdexcept>
#include "sorting.h"
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

Date& Date::operator++(int)
{
    day++;
    correct();

    return *this;
}

Date &Date::operator+=(int num)
{
    day += num;
    correct();

    return *this;
}

void Date::randomize(int interval)
{

    day = getRandomInt(1, 31);
    month = getRandomInt(1, 12);
    year = getRandomInt(2000-interval/2, 2000+interval/2);

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

QString Date::getTwoRowsText()
{
    return (toISOtime(day) + "." + toISOtime(month) + "\n" + QString::number(year));
}

Date::operator QString()
{
    return (toISOtime(day) + "." + toISOtime(month) + " " + QString::number(year));
}

Date *randomDateArray(unsigned int size)
{
    if (size < 1) throw std::range_error("Size of array must be > 0");

    Date* arr = new Date[size];

    for (unsigned int i = 0; i < size; i++)
    {
        Date d;
        d.randomize(size+10);
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

Date *sortedDateArray(unsigned int size, bool ascending)
{
    Date* arr = new Date[size];
    Date date = {1, 1, 2000-(int)(size/7300 < 1 ? size/73 : size/730)-1};

    unsigned int elem_idx = (ascending ? 0 : size-1);
    int shift = (ascending ? 1 : -1);

    for (; elem_idx < size; elem_idx += shift)
    {
        arr[elem_idx] = date;
        date += getRandomInt(1, 400);
    }

    return arr;
}

Date *almostSortedDateArray(unsigned int size, bool ascending)
{
    Date* arr = sortedDateArray(size, ascending);

    for (unsigned int i = 0; i < size/8 + 1; i++) {
        int idx1 = getRandomInt(0, size-1), idx2 = getRandomInt(0, size-1);
        _swap(arr[idx1], arr[idx2]);
    }

    return arr;
}

dateElem *dateArrToDateElemArr(Date *dateArr, unsigned int size)
{
    dateElem* dateElemArr = new dateElem[size];

    for (unsigned int idx = 0; idx < size; idx++)
    {
        dateElemArr[idx] = dateElem{dateArr[idx], idx};
    }

    return dateElemArr;
}

Date *dateElemArrToDateArr(dateElem *dateElemArr, unsigned int size)
{
    Date* dateArr = new Date[size];

    for(unsigned int idx = 0; idx < size; idx++)
    {
        dateArr[idx] = dateElemArr[idx].date;
    }

    return dateArr;
}

bool operator==(dateElem dE1, dateElem dE2)
{
    return dE1.date == dE2.date;
}

bool operator>(dateElem dE1, dateElem dE2)
{
    return dE1.date > dE2.date;
}

bool operator>=(dateElem dE1, dateElem dE2)
{
    return dE1.date >= dE2.date;
}

bool operator<(dateElem dE1, dateElem dE2)
{
    return dE1.date < dE2.date;
}

bool operator<=(dateElem dE1, dateElem dE2)
{
    return dE1.date <= dE2.date;
}
