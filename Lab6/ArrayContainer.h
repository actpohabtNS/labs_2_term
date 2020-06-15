#ifndef ARRAYCONTAINER_H
#define ARRAYCONTAINER_H

#include <vector>

#include "container.h"

template <class T>
class ArrayContainer : public Container<T>
{
private:
    T* _array;
    unsigned _size;
    unsigned _capacity;

    void _resize(const unsigned& newCapacity);

public:
    class Iterator
    {
    private:
        T* _array;
        unsigned _index;

    public:
        explicit Iterator(T* array, unsigned index);
        virtual ~Iterator() = default;

        T& operator*();
        T* operator->();

        Iterator& operator++();
        Iterator& operator+=(int n);

        bool operator!=(const Iterator& other);
    };

    class ConstIterator
    {
    private:
        T* _array;
        unsigned _index;

    public:
        explicit ConstIterator(T* array, unsigned index);
        virtual ~ConstIterator() = default;

        T& operator*();
        T* operator->();

        ConstIterator& operator++();
        ConstIterator& operator+=(int n);

        bool operator!=(const ConstIterator& other);
    };

    ArrayContainer();
    explicit ArrayContainer(unsigned size);
    ArrayContainer(unsigned size, T val);
    ArrayContainer(const std::initializer_list<T>& values);

    ~ArrayContainer() override;

    T& operator[](unsigned index);
    T& at(unsigned index);

    const T& operator[](unsigned index) const;
    const T& at(unsigned index) const;

    void push(unsigned idx, const T& val) override;
    void pushFront(const T& val) override;
    void pushBack(const T& val) override;

    void pop(unsigned idx) override;
    void popFront() override;
    void popBack() override;

    void clear() override;
    void shrinkToFit();

    [[nodiscard]] virtual const unsigned& size() const override;
    [[nodiscard]] virtual const unsigned& capacity() const;
    [[nodiscard]] virtual T& front() override;
    [[nodiscard]] virtual T& back() override;
    [[nodiscard]] virtual const T& front() const override;
    [[nodiscard]] virtual const T& back() const override;
    [[nodiscard]] virtual bool empty() const override;

    Iterator begin();
    Iterator end();

    ConstIterator begin() const;
    ConstIterator end() const;
};


// ----------------------------------- Iterator -----------------------------------

template<class T>
ArrayContainer<T>::Iterator::Iterator(T *array, unsigned index)
    : _array(array), _index(index) {}

template<class T>
T &ArrayContainer<T>::Iterator::operator*()
{
    return this->_array[this->_index];
}

template<class T>
T *ArrayContainer<T>::Iterator::operator->()
{
    return &this->_array[this->_index];
}

template<class T>
typename ArrayContainer<T>::Iterator &ArrayContainer<T>::Iterator::operator++()
{
    this->_index++;
    return *this;
}

template<class T>
typename ArrayContainer<T>::Iterator &ArrayContainer<T>::Iterator::operator+=(int n)
{
    this->_index += n;
    return this;
}

template<class T>
bool ArrayContainer<T>::Iterator::operator!=(const ArrayContainer::Iterator &other)
{
    return this->_index != other._index;
}


// ----------------------------------- ConstIterator -----------------------------------

template<class T>
ArrayContainer<T>::ConstIterator::ConstIterator(T *array, unsigned index)
    : _array(array), _index(index) {}

template<class T>
T &ArrayContainer<T>::ConstIterator::operator*()
{
    return this->_array[this->_index];
}

template<class T>
T *ArrayContainer<T>::ConstIterator::operator->()
{
    return *this->_array[this->_index];
}

template<class T>
typename ArrayContainer<T>::ConstIterator &ArrayContainer<T>::ConstIterator::operator++()
{
    this->_index++;
    return *this;
}

template<class T>
typename ArrayContainer<T>::ConstIterator &ArrayContainer<T>::ConstIterator::operator+=(int n)
{
    this->_index += n;
    return *this;
}

template<class T>
bool ArrayContainer<T>::ConstIterator::operator!=(const ArrayContainer::ConstIterator &other)
{
    return this->_index != other._index;
}


// ----------------------------------- ArrayContainer -----------------------------------

template<class T>
void ArrayContainer<T>::_resize(const unsigned &newCapacity)
{
    this->_capacity = newCapacity;

    T* newArr = new T[newCapacity];

    for (unsigned idx = 0; idx < this->_size; idx++)
        newArr[idx] = this->_array[idx];

    delete this->_array;

    this->_array = newArr;
}

template<class T>
ArrayContainer<T>::ArrayContainer()
    : _array(nullptr), _size(0), _capacity(0) {}

template<class T>
ArrayContainer<T>::ArrayContainer(unsigned size)
    : _size(size), _capacity(size)
{
    this->_array = new T[size];
}

template<class T>
ArrayContainer<T>::ArrayContainer(unsigned size, T val)
    : _size(size), _capacity(size)
{
    this->_array = new T[size];

    for (unsigned idx = 0; idx < size; idx++)
        this->_array[idx] = val;
}

template<class T>
ArrayContainer<T>::ArrayContainer(const std::initializer_list<T> &values)
    : _size(values.size()), _capacity(values.size())
{
    this->_array = new T[values.size()];

    for (unsigned idx = 0; idx < values.size(); idx++)
        this->_array[idx] = values[idx];
}

template<class T>
ArrayContainer<T>::~ArrayContainer()
{
    delete this->_array;
}

template<class T>
T &ArrayContainer<T>::operator[](unsigned index)
{
    if (index >= this->_size)
        throw std::out_of_range("Index is out of range!");

    return this->_array[index];
}

template<class T>
T &ArrayContainer<T>::at(unsigned index)
{
    if (index >= this->_size)
        throw std::out_of_range("Index is out of range!");

    return this->_array[index];
}

template<class T>
const T &ArrayContainer<T>::operator[](unsigned index) const
{
    if (index >= this->_size)
        throw std::out_of_range("Index is out of range!");

    return this->_array[index];
}

template<class T>
const T &ArrayContainer<T>::at(unsigned index) const
{
    if (index >= this->_size)
        throw std::out_of_range("Index is out of range!");

    return this->_array[index];
}

template<class T>
void ArrayContainer<T>::push(unsigned idx, const T &val)
{
    if (idx > this->_size)
        return;

    if (this->_size == 0)
    {
        this->pushBack(val);
        return;
    }

    if (this->_size == this->_capacity)
    {
        this->_capacity *= 2;
        T* newArr = new T[this->_capacity];

        for (unsigned i = 0; i < idx; i++)
            newArr[i] = this->_array[i];

        newArr[idx] = val;

        for (unsigned i = idx; i < this->_size; i++)
            newArr[i + 1] = this->_array[i];

        delete [] this->_array;
        this->_array = newArr;
        this->_size++;

        return;
    }

    for (unsigned i = this->_size; i > idx; i--)
        this->_array[i] = this->_array[i - 1];

    this->_array[idx] = val;
    this->_size++;
}

template<class T>
void ArrayContainer<T>::pushFront(const T &val)
{
    this->push(0, val);
}

template<class T>
void ArrayContainer<T>::pushBack(const T &val)
{
    if (this->_size == 0 && this->_capacity == 0)
    {
        this->_size++;
        this->_capacity++;
        this->_array = new T[1];
        this->_array[0] = val;

        return;
    }

    if (this->_size == this->_capacity)
        this->_capacity *= 2;

    this->_array[this->_size] = val;
    this->_size++;
}

template<class T>
void ArrayContainer<T>::pop(unsigned idx)
{
    if (idx > this->_size)
        return;

    for (unsigned i = idx; i < this->_size - 1; idx++)
        this->_array[i] = this->_array[i + 1];

    this->_size--;

    if (this->_size < this->_capacity / 4)
        this->_capacity /= 2;
}

template<class T>
void ArrayContainer<T>::popFront()
{
    this->pop(0);
}

template<class T>
void ArrayContainer<T>::popBack()
{
    if (this->_size == 0)
        return;

    this->_size--;

    if (this->_size < this->_capacity / 4)
        this->_capacity /= 2;
}

template<class T>
void ArrayContainer<T>::clear()
{
    delete [] this->_array;
    this->_array = nullptr;

    this->_size = 0;
}

template<class T>
void ArrayContainer<T>::shrinkToFit()
{
    this->_capacity = this->_size;
}

template<class T>
const unsigned &ArrayContainer<T>::size() const
{
    return this->_size;
}

template<class T>
const unsigned &ArrayContainer<T>::capacity() const
{
    return this->_capacity;
}

template<class T>
T &ArrayContainer<T>::front()
{
    if (this->_size == 0)
        throw std::out_of_range("Index is out of range!");

    return this->_array[0];
}

template<class T>
T &ArrayContainer<T>::back()
{
    if (this->_size == 0)
        throw std::out_of_range("Index is out of range!");

    return this->_array[this->_size - 1];
}

template<class T>
const T &ArrayContainer<T>::front() const
{
    if (this->_size == 0)
        throw std::out_of_range("Index is out of range!");

    return this->_array[0];
}

template<class T>
const T &ArrayContainer<T>::back() const
{
    if (this->_size == 0)
        throw std::out_of_range("Index is out of range!");

    return this->_array[this->_size - 1];
}

template<class T>
bool ArrayContainer<T>::empty() const
{
    return this->_size == 0;
}

template<class T>
typename ArrayContainer<T>::Iterator ArrayContainer<T>::begin()
{
    return ArrayContainer::Iterator(this->_array, 0);
}

template<class T>
typename ArrayContainer<T>::Iterator ArrayContainer<T>::end()
{
    return ArrayContainer::Iterator(this->_array, this->_size);
}

template<class T>
typename ArrayContainer<T>::ConstIterator ArrayContainer<T>::begin() const
{
    return ArrayContainer::ConstIterator(this->_array, 0);
}

template<class T>
typename ArrayContainer<T>::ConstIterator ArrayContainer<T>::end() const
{
    return ArrayContainer::ConstIterator(this->_array, this->_size);
}

#endif // ARRAYCONTAINER_H
