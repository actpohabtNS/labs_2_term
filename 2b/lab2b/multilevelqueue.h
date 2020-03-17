#ifndef MULTILEVELQUEUE_H
#define MULTILEVELQUEUE_H
#include "queue.h"
#include "priorityqueue.h"

template<typename T>
struct QueueNode{
    Queue<T> queue;
    uint prior;
    QueueNode<T>* prevQueue;
    QueueNode<T>* nextQueue;
};

template<typename T>
class MultilevelQueue
{
public:
    MultilevelQueue() {
        _firstQueue = nullptr;
        _lastQueue = nullptr;
    };

    MultilevelQueue(T data, uint prior) {
        Queue<T> queue(data);
        QueueNode<T>* queueNode = new QueueNode<T>{queue, prior, nullptr, nullptr};

        _firstQueue = queueNode;
        _lastQueue = queueNode;
    }

    void push(T data, uint prior) {

        QueueNode<T>* temp = _firstQueue;

        while (temp != nullptr) {

            if (temp->prior == prior) {

                temp->queue.enqueue(data);
                return;

            }

            if (prior < temp->prior) {

                Queue<T> newQueue(data);
                QueueNode<T>* newQueueNode = new QueueNode<T>{newQueue, prior, nullptr, temp};

                if (temp != _firstQueue) {

                    newQueueNode->prevQueue = temp->prevQueue;
                    temp->prevQueue->nextQueue = newQueueNode;

                } else {

                    _firstQueue = newQueueNode;

                }

                temp->prevQueue = newQueueNode;
                return;

            }

            temp = temp->nextQueue;

        }

        Queue<T> newQueue(data);
        QueueNode<T>* newQueueNode = new QueueNode<T>{newQueue, prior, nullptr, nullptr};

        if (_firstQueue == nullptr) {

            _firstQueue = newQueueNode;

        } else {

            newQueueNode->prevQueue = _lastQueue;
            _lastQueue->nextQueue = newQueueNode;

        }

        _lastQueue = newQueueNode;

    }

    T* pop() {

        if (_firstQueue == nullptr) return nullptr;

        T* data = _lastQueue->queue.dequeue();

        if (_lastQueue->queue.isEmpty()) {

            _lastQueue = _lastQueue->prevQueue;

            if (_lastQueue == nullptr) {

                _firstQueue = nullptr;

            } else {

                 _lastQueue->nextQueue = nullptr;

            }

        }

        return data;

    }

    T* peek() {
        if (_firstQueue == nullptr) return nullptr;

        return  _firstQueue->queue.peek();
    }

    void print() {

        QueueNode<T>* temp = _lastQueue;

        while (temp != nullptr) {

            qDebug() << "=========" << QString::number(temp->prior) << ":" << "=========";
            temp->queue.print();
            qDebug() << " ";
            temp = temp->prevQueue;

        }

    }

    bool levelExists(uint prior) {
        QueueNode<T>* temp = _firstQueue;

        while (temp != nullptr) {

            if (temp->prior == prior) return true;
            temp = temp->nextQueue;

        }

        return false;
    }

    void loadPrQ(PriorityQueue<T> prQ) {

        while (!prQ.isEmpty()) {

            uint maxPr = prQ.getMaxPr();
            push(*prQ.pop(), maxPr);

        }

    }

    QueueNode<T>* firstQueue() {
        return _firstQueue;
    }

    QueueNode<T>* lastQueue() {
        return _lastQueue;
    }

    bool isEmpty() {
        return _firstQueue == nullptr;
    }


private:
    QueueNode<T>* _firstQueue;
    QueueNode<T>* _lastQueue;
};

#endif // MULTILEVELQUEUE_H
