#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <QString>

#include "sortedList.h"
#include "listContainer.h"

template <typename T>
class LinkedList : public SortedList<T>
{
private:
    ListContainer<T> _container;
    QString _type;

public:
    LinkedList();
    LinkedList(std::initializer_list<T>& list);
    ~LinkedList() = default;

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

// ----------------------------------- LinkedList -----------------------------------

template<typename T>
LinkedList<T>::LinkedList()
    : _type("LinkedList") {}

template<typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> &list)
    : _type("LinkedList")
{
    for (const T& elem : list)
    {
        this->_container.push(elem);
    }
}

template<typename T>
void LinkedList<T>::fill(uint quan)
{
    for (uint idx = 0; idx < quan; idx++)
        this->push(getRandomInt(-100, 100));
}

template<typename T>
void LinkedList<T>::push(const T &elem)
{
    if (this->_container.empty())
    {
        this->_container.pushBack(elem);
        return;
    }

    int idx = 0;

    for (const T& e : this->_container)
    {
        if (e < elem)
            idx++;
        else
            break;
    }

    this->_container.push(idx, elem);
}

template<typename T>
void LinkedList<T>::pop(const T &elem)
{
    if (elem < this->_container.front() || this->_container.back() < elem)
        return;

    int idx = 0;

    for (typename ListContainer<T>::Iterator it = this->_container.begin(); it != this->_container.end();)
    {
        if (*it == elem)
        {
             ++it;
             this->_container.pop(idx);
        } else if (*it > elem)
            break;
        else
        {
            ++it;
            idx++;
        }
    }
}

template<typename T>
bool LinkedList<T>::exist(const T &elem) const
{
    if (elem < this->_container.front() || this->_container.back() < elem)
        return false;

    for (typename ListContainer<T>::ConstIterator it = this->_container.begin(); it != this->_container.end();)
    {
        if (*it == elem)
             return true;
        else if (*it > elem)
            return false;
        else
            ++it;
    }
}

template<typename T>
std::vector<T> LinkedList<T>::range(const T &min, const T &max) const
{
    if (min > max)
        return {};

    if (max < this->_container.front() || this->_container.back() < min)
        return {};

    std::vector<T> res;

    for (typename ListContainer<T>::ConstIterator it = this->_container.begin(); it != this->_container.end();)
    {
        if (min <= *it && *it <= max)
            res.emplace_back(*it);

        ++it;
    }

    return res;
}

template<typename T>
const T &LinkedList<T>::front() const
{
    return this->_container.front();
}

template<typename T>
const T &LinkedList<T>::back() const
{
    return this->_container.back();
}

template<typename T>
QString LinkedList<T>::QStr() const
{
    QString QStr;
    QTextStream *stream = new QTextStream(&QStr);

    for (const T& elem : this->_container)
        *stream << elem << " ";

    return QStr;
}

template<typename T>
void LinkedList<T>::print() const
{
    qDebug() << this->QStr();
}

template<typename T>
QString LinkedList<T>::type() const
{
    return this->_type;
}

template<typename T>
bool LinkedList<T>::empty() const
{
    return this->_container.empty();
}

template<typename T>
uint LinkedList<T>::size() const
{
    return this->_container.size();
}
#endif // LINKEDLIST_H
