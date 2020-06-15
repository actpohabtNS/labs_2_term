#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "sortedList.h"
#include "ArrayContainer.h"

template <class T>
class ArrayList : public SortedList<T>
{
private:
    ArrayContainer<T> _container;
    QString _type;

    [[nodiscard]] unsigned _binarySearch(const T& elem) const;

public:
    ArrayList();
    ArrayList(std::initializer_list<T>& list);
    ~ArrayList() = default;

    void fill(uint quan) override;

    void push(const T& elem) override;
    void pop(const T& elem) override;
    bool exist(const T& elem) const override;

    std::vector<T> range(const T& min, const T& max) const override;

    const T& front() const override;
    const T& back() const override;

    QString QStr() const override;
    void print() const override;

    QString type() const override;

    bool empty() const override;
    uint size() const override;
};


// ----------------------------------- ArrayList -----------------------------------

#endif // ARRAYLIST_H

template<class T>
unsigned ArrayList<T>::_binarySearch(const T &elem) const
{
    if (this->_container.empty())
        return 0;

    unsigned left = 0;
    unsigned mid = 0;
    unsigned right = this->_container.size() - 1;

    while (left <= right)
    {
        mid = (left + right) / 2;

        if (this->_container[mid] == elem)
            return mid;
        else if (this->_container[mid] > elem)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return this->_container[mid] < elem ? mid + 1 : mid;
}

template<class T>
ArrayList<T>::ArrayList()
    : _type("ArrayList") {}

template<class T>
ArrayList<T>::ArrayList(std::initializer_list<T> &list)
    : _type("ArrayList")
{
    for (const T& elem : list)
        this->_container.push(elem);
}

template<class T>
void ArrayList<T>::fill(uint quan)
{
    for (uint idx = 0; idx < quan; idx++)
        this->push(getRandomInt(-100, 100));
}

template<class T>
void ArrayList<T>::push(const T &elem)
{
    this->_container.push(this->_binarySearch(elem), elem);
}

template<class T>
void ArrayList<T>::pop(const T &elem)
{
    if (!this->exist(elem))
        return;

    this->_container.pop(this->_binarySearch(elem));
}

template<class T>
bool ArrayList<T>::exist(const T &elem) const
{
    return this->_container[this->_binarySearch(elem)] == elem;
}

template<class T>
std::vector<T> ArrayList<T>::range(const T &min, const T &max) const
{
    if (min > max)
        return {};

    if (max < this->_container.front() || this->_container.back() < min)
        return {};

    std::vector<T> res;

    for (typename ArrayContainer<T>::ConstIterator it = this->_container.begin(); it != this->_container.end();)
    {
        if (min <= *it && *it <= max)
            res.emplace_back(*it);

        ++it;
    }

    return res;
}

template<class T>
const T &ArrayList<T>::front() const
{
    return this->_container.front();
}

template<class T>
const T &ArrayList<T>::back() const
{
    return this->_container.back();
}

template<class T>
QString ArrayList<T>::QStr() const
{
    QString QStr;
    QTextStream *stream = new QTextStream(&QStr);

    for (const T& elem : this->_container)
        *stream << elem << " ";

    return QStr;
}

template<class T>
void ArrayList<T>::print() const
{
    qDebug() << this->QStr();
}

template<class T>
QString ArrayList<T>::type() const
{
    return this->_type;
}

template<class T>
bool ArrayList<T>::empty() const
{
    return this->_container.empty();
}

template<class T>
uint ArrayList<T>::size() const
{
    return this->_container.size();
}
