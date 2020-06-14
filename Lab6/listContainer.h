#ifndef LISTCONTAINER_H
#define LISTCONTAINER_H

#include <stdexcept>

#include "container.h"

template <class T>
class ListContainer : public Container<T>
{
public:
    class Node;
    class Iterator;
    class ConstIterator;

    class Node
    {
    private:
        friend ListContainer;
        friend Iterator;
        friend ConstIterator;

        T _value;
        Node* _next;

    public:
        explicit Node(T value, Node* next = nullptr);
        virtual ~Node() = default;

        const T& value() const;
        const Node* next() const;
    };

    class Iterator
    {
    private:
        Node* _node;

    public:
        explicit Iterator(Node* node = nullptr);
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
        Node* _node;

    public:
        explicit ConstIterator(Node* node = nullptr);
        virtual ~ConstIterator() = default;

        T& operator*();
        T* operator->();

        ConstIterator& operator++();
        ConstIterator& operator+=(int n);

        bool operator!=(const ConstIterator& other);
    };

    ListContainer();
    explicit ListContainer(unsigned size, T val);
    ListContainer(const std::initializer_list<T>& values);

    ~ListContainer() override;

    void push(int idx, const T& val) override;
    void pushFront(const T& val) override;
    void pushBack(const T& val) override;

    void pop(int idx) override;
    void popFront() override;
    void popBack() override;

    void clear() override;

    [[nodiscard]] virtual const unsigned& size() const override;
    [[nodiscard]] virtual T& front() override;
    [[nodiscard]] virtual T& back() override;
    [[nodiscard]] virtual const T& front() const override;
    [[nodiscard]] virtual const T& back() const override;
    [[nodiscard]] virtual bool empty() const override;

    Iterator begin();
    Iterator end();

    ConstIterator begin() const;
    ConstIterator end() const;

private:
    unsigned _size;
    Node* _begin;
    Node* _end;
};

// ----------------------------------- Node -----------------------------------

template<class T>
ListContainer<T>::Node::Node(T value, ListContainer::Node *next)
    : _value(value), _next(next) {}

template<class T>
const T &ListContainer<T>::Node::value() const
{
 return this->_value;
}

template<class T>
const typename ListContainer<T>::Node *ListContainer<T>::Node::next() const
{
    return this->_next;
}


// ----------------------------------- Iterator -----------------------------------

template<class T>
ListContainer<T>::Iterator::Iterator(ListContainer::Node *node)
    : _node(node) {}

template<class T>
T &ListContainer<T>::Iterator::operator*()
{
    return this->_node->_value;
}

template<class T>
T *ListContainer<T>::Iterator::operator->()
{
    return &this->_node->_value;
}

template<class T>
typename ListContainer<T>::Iterator &ListContainer<T>::Iterator::operator++()
{
    this->_node = this->_node->_next;
    return *this;
}

template<class T>
typename ListContainer<T>::Iterator &ListContainer<T>::Iterator::operator+=(int n)
{
    for (int i = 0; i < n; i++)
                this->_node = this->_node->_next;

    return *this;
}

template<class T>
bool ListContainer<T>::Iterator::operator!=(const ListContainer::Iterator &other)
{
    return this->_node != other._node;
}


// ----------------------------------- ConstIterator -----------------------------------

template<class T>
ListContainer<T>::ConstIterator::ConstIterator(ListContainer::Node *node)
    : _node(node) {}


template<class T>
T &ListContainer<T>::ConstIterator::operator*()
{
    return this->_node->_value;
}

template<class T>
T *ListContainer<T>::ConstIterator::operator->()
{
    return &this->_node->_value;
}


template<class T>
typename ListContainer<T>::ConstIterator &ListContainer<T>::ConstIterator::operator++()
{
    this->_node = this->_node->_next;
    return *this;
}

template<class T>
typename ListContainer<T>::ConstIterator &ListContainer<T>::ConstIterator::operator+=(int n)
{
    for (int i = 0; i < n; i++)
                this->_node = this->_node->_next;

    return *this;
}


template<class T>
bool ListContainer<T>::ConstIterator::operator!=(const ListContainer::ConstIterator &other)
{
    return this->_node != other._node;
}


// ----------------------------------- ListContainer -----------------------------------

template<class T>
ListContainer<T>::ListContainer()
    : _size(0), _begin(nullptr), _end(nullptr) {}

template<class T>
ListContainer<T>::ListContainer(unsigned size, T val)
    : _size(size)
{
    this->_begin = new Node(val);
    Node* prevNode = this->_begin;

    for (unsigned idx = 1; idx < this->_size; idx++)
    {
        Node* newNode = new Node(val);

        prevNode->_next = newNode;
        prevNode = prevNode->_next;
    }

    this->_end = prevNode;
}

template<class T>
ListContainer<T>::ListContainer(const std::initializer_list<T> &values)
 : _size(values.size())
{
    this->_begin = new Node(values[0]);
    Node* prevNode = this->_begin;

    for (const T& val : values)
    {
        Node* newNode = new Node(val);

        prevNode->_next = newNode;
        prevNode = prevNode->_next;
    }

    this->_end = prevNode;
}

template<class T>
ListContainer<T>::~ListContainer()
{
    Node* curr = this->_begin;
    Node* next;

    while (curr)
    {
        next = curr->_next;
        delete curr;
        curr = next;
    }
}

template<class T>
void ListContainer<T>::push(int idx, const T &val)
{
    qDebug() << "pushing" << val << idx;

    if (idx < 0 || idx > this->_size)
        return;

    if (idx == 0)
    {
        this->pushFront(val);
        return;
    }

    if (idx == this->_size)
    {
        this->pushBack(val);
        return;
    }

    Node* newNode = new Node(val);

    Node* curr = this->_begin;

    for (int i = 1; i < idx; i++)
        curr = curr->_next;

    Node* next = curr->_next;

    curr->_next = newNode;
    newNode->_next = next;

    this->_size++;
}

template<class T>
void ListContainer<T>::pushFront(const T &val)
{
    Node* newNode = new Node(val, this->_begin);

    this->_begin = newNode;

    if (!this->_end)
    {
        this->_begin->_next = newNode;
        this->_end = newNode;
    }

    this->_size++;
}

template<class T>
void ListContainer<T>::pushBack(const T &val)
{
    Node* newNode = new Node(val);

    if (!this->_begin)
        this->_begin = newNode;
    else
        this->_end->_next = newNode;

    this->_end = newNode;

    this->_size++;
}

template<class T>
void ListContainer<T>::pop(int idx)
{
    if (idx < 0 || idx > this->_size-1)
        return;

    if (idx == 0)
    {
        this->popFront();
        return;
    }

    if (idx == this->_size)
    {
        this->popBack();
        return;
    }

    Node* curr = this->_begin;
    Node* prev = this->_begin;

    for (int i = 0; i < idx; i++)
    {
        prev = curr;
        curr = curr->_next;
    }

    Node* next = curr->_next;
    delete curr;
    prev->_next = next;

    this->_size--;
}

template<class T>
void ListContainer<T>::popFront()
{
    if (this->_size == 0)
        return;

    if (this->_size == 1)
    {
        delete this->_begin;
        this->_begin = nullptr;
        this->_end = nullptr;
        this->_size--;
        return;
    }

    Node* next = this->_begin->_next;
    delete this->_begin;
    this->_begin = next;
    this->_size--;
}

template<class T>
void ListContainer<T>::popBack()
{
    if (this->_size == 0)
        return;

    if (this->_size == 1)
    {
        delete this->_end;
        this->_begin = nullptr;
        this->_end = nullptr;
        this->_size--;
        return;
    }

    Node* curr = this->_begin;
    Node* prev = this->_begin;

    for (unsigned i = 0; i < this->_size - 1; i++)
    {
        prev = curr;
        curr = curr->_next;
    }

    prev->_next = nullptr;
    delete this->_end;
    this->_end = prev;
    this->_size--;
}

template<class T>
void ListContainer<T>::clear()
{
    if (this->_size == 0)
        return;

    Node* curr = this->_begin;
    Node* next;

    for (unsigned i = 0; i < this->_size - 1; i++)
    {
        next = curr->_next;
        delete curr;
        curr = next;
    }

    this->_begin = nullptr;
    this->_end = nullptr;
    this->_size = 0;
}

template<class T>
const unsigned &ListContainer<T>::size() const
{
    return this->_size;
}

template<class T>
T &ListContainer<T>::front()
{
    if (this->_size == 0)
        throw std::out_of_range("Index is out of range!");

    return this->_begin->_value;
}

template<class T>
T &ListContainer<T>::back()
{
    if (this->_size == 0)
        throw std::out_of_range("Index is out of range!");

    return this->_end->_value;
}

template<class T>
const T &ListContainer<T>::front() const
{
    if (this->_size == 0)
        throw std::out_of_range("Index is out of range!");

    return this->_begin->_value;
}

template<class T>
const T &ListContainer<T>::back() const
{
    if (this->_size == 0)
        throw std::out_of_range("Index is out of range!");

    return this->_end->_value;
}

template<class T>
bool ListContainer<T>::empty() const
{
    return this->_size == 0;
}

template<class T>
typename ListContainer<T>::Iterator ListContainer<T>::begin()
{
    return ListContainer::Iterator(this->_begin);
}

template<class T>
typename ListContainer<T>::Iterator ListContainer<T>::end()
{
    return ListContainer::Iterator(this->_end->_next);
}

template<class T>
typename ListContainer<T>::ConstIterator ListContainer<T>::begin() const
{
    return ListContainer::ConstIterator(this->_begin);
}

template<class T>
typename ListContainer<T>::ConstIterator ListContainer<T>::end() const
{
    return ListContainer::ConstIterator(this->_end->_next);
}


#endif // LISTCONTAINER_H
