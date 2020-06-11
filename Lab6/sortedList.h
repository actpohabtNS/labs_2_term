#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include <vector>
#include <QString>

template <typename T>
class SortedList {
public:
    SortedList() = default;
    virtual ~SortedList() = default;

    virtual void fill(uint quan) = 0;

    virtual void add(const T& elem) = 0;
    virtual void remove(const T& elem) = 0;
    virtual bool includes(const T& elem) const = 0;

    virtual std::vector<T> range(const T& min, const T& max) const = 0;

    virtual QString QStr() const = 0;
    virtual void print() const = 0;

    virtual bool empty() const = 0;
    virtual uint size() const = 0;
};

#endif // SORTEDLIST_H
