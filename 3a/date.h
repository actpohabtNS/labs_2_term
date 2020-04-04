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

    void randomize();
    void correct();

    virtual operator QString();
};

int cutDay(int& day, int max);

QString toISOtime(int timeUnit);

Date* getRandomDateArray(unsigned int size);

#endif // DATE_H
