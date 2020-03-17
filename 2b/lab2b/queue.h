#ifndef QUEUE_H
#define QUEUE_H
#include <QDebug>
#include <stdexcept>

template <typename T>
struct QNode {
    T data;
    QNode* prev;
    QNode* next;
};

template <typename T>
class Queue
{ 
public:
    Queue() {
        _begin = nullptr;
        _end = nullptr;
    };

    Queue(T data) {
        QNode<T>* node = new QNode<T>{data, nullptr, nullptr};
        _begin = node;
        _end = node;
    }

    void enqueue(T data) {
        QNode<T>* node = new QNode<T>{data, nullptr, nullptr};

        if (_begin == nullptr) {

            _begin = node;
            _end = node;

        } else {

            _begin->prev = node;
            node->next = _begin;
            _begin = node;

        }

    }

    T* dequeue() {
        if (isEmpty()) return nullptr;


        QNode<T>* returnableNode = _end;
        _end = _end->prev;

        if (_end == nullptr) {

            _begin = nullptr;

        } else {

            _end->next = nullptr;

        }

        return &returnableNode->data;

    }

    T* peek() {
        if (isEmpty()) return nullptr;

        return &(_end->data);
    }

    bool isEmpty() {
        return _begin == nullptr;
    }

    QNode<T>* begin() {
        return _begin;
    }

    QNode<T>* end() {
        return _end;
    }

    void print() {
        QNode<T>* temp = _end;

        while (temp != nullptr) {

            qDebug() << temp->data;
            temp = temp->prev;

        }
    }

private:
    QNode<T>* _begin;
    QNode<T>* _end;
};

#endif // QUEUE_H
