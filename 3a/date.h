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
    Date& operator+=(int num);
    virtual operator QString();

    void randomize(int interval);
    void correct();
    QString getTwoRowsText();

};

struct dateElem{
    Date date;
    unsigned int index;
};

bool operator==(dateElem dE1, dateElem dE2);
bool operator>(dateElem dE1, dateElem dE2);
bool operator>=(dateElem dE1, dateElem dE2);
bool operator<(dateElem dE1, dateElem dE2);
bool operator<=(dateElem dE1, dateElem dE2);

int cutDay(int& day, int max);

QString toISOtime(int timeUnit);

Date* randomDateArray(unsigned int size);

Date* sortedDateArray(unsigned int size, bool ascending);

Date* almostSortedDateArray(unsigned int size, bool ascending = true);

dateElem* dateArrToDateElemArr(Date* dateArr, unsigned int size);

Date* dateElemArrToDateArr(dateElem* dateElemArr, unsigned int size);

#endif // DATE_H
