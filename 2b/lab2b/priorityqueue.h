#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <QDebug>
#include "task.h"

template <typename T>
struct Node {
    T data;
    uint priority;
    Node* next;
    Node* prev;
};

template <typename T>
class PriorityQueue
{
public:
    PriorityQueue() {
      begin = nullptr;
      end = nullptr;
    };

    PriorityQueue(T data) {
        Node<T>* node = new Node<T>(data);

        begin = node;
        end = node;
    }

    bool isEmpty() {
        return (begin == nullptr);
    }

    void push(T data, uint priority) {

        Node<T>* node = new Node<T>{data, priority, nullptr, nullptr};

        if (begin == nullptr) {

            node->next = begin;

            begin = node;
            end = node;

        } else {

            if (priority > getMaxPr()) {

                node->prev = end;
                end->next = node;

                end = node;

                return;
            }

            if (priority <= getMinPr()) {

                node->next = begin;
                begin->prev = node;

                begin = node;

                return;

            }

            Node<T>* tempNode = begin;

            while (priority > tempNode->priority) {
                tempNode = tempNode->next;
            }

            node->next = tempNode;
            node->prev = tempNode->prev;


            tempNode->prev->next = node;
            tempNode->prev = node;

        }

    }

    T* pop() {
        if (begin == nullptr) return nullptr;

        Node<T>* temp = end;
        end->prev->next = nullptr;

        return temp->data;
    }


    uint getMaxPr(){

        if (end == nullptr) return -1;

        return end->priority;

    }

    uint getMinPr() {
        if (begin == nullptr) return -1;

        return begin->priority;
    }

    void print() {
        if (begin == nullptr) return;

        Node<T>* node = end;

        while(node != begin) {

            qDebug() << node->data;
           //node->data->print();       //TO THINK
           node = node->prev;

        }

        qDebug() << node->data;
        //node->data->print();

    };


private:
    Node<T>* begin;
    Node<T>* end;
};

#endif // PRIORITYQUEUE_H
