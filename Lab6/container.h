#ifndef CONTAINER_H
#define CONTAINER_H

#include <initializer_list>
#include <QtDebug>

template <class T>
class Container
{
public:
    Container() = default;
    virtual ~Container() = default;

    virtual void push(int idx, const T& val) = 0;
    virtual void pushFront(const T& val) = 0;
    virtual void pushBack(const T& val) = 0;

    virtual void pop(int idx) = 0;
    virtual void popFront() = 0;
    virtual void popBack() = 0;

    virtual void clear() = 0;

    [[nodiscard]] virtual const unsigned& size() const = 0;
    [[nodiscard]] virtual T& front() = 0;
    [[nodiscard]] virtual T& back() = 0;
    [[nodiscard]] virtual const T& front() const = 0;
    [[nodiscard]] virtual const T& back() const = 0;
    [[nodiscard]] virtual bool empty() const = 0;
};

#endif // CONTAINER_H
