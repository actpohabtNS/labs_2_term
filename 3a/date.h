#ifndef DATE_H
#define DATE_H
#include <QString>

class Date
{
    int day, month, year;

public:
    Date();
    Date(int day, int month, int year);

    bool operator > (Date d);
    bool operator == (Date d);
    bool operator >= (Date d);
    bool operator < (Date d);
    bool operator <= (Date d);
    Date& operator++(int);
    virtual operator QString();

    void randomize(int n);
    void correct();

};

int cutDay(int& day, int max);

QString toISOtime(int timeUnit);

Date* randomDateArray(unsigned int size);

Date* sortedDateArray(unsigned int size, bool ascending);

Date* almostSortedDateArray(unsigned int size, bool ascending = true);

#endif // DATE_H
