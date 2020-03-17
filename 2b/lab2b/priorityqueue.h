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

    PriorityQueue(T data, uint priority) {
        Node<T>* node = new Node<T>{data, priority, nullptr, nullptr};

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

        end = end->prev;

        if (end == nullptr) {

            end = nullptr;
            begin = nullptr;

        } else {

            end->next = nullptr;

        }


        return &(temp->data);
    }


    void remove(T* data) {
       if (begin == nullptr) return;

       Node<T>* deletingNode;

       if (begin->data == data) {
          deletingNode = begin;

          begin = begin->next;
          begin->prev = nullptr;

          delete deletingNode;
          return;
       }

       if (end->data == data) {
          deletingNode = end;

          end = end->prev;
          end->next = nullptr;

          delete deletingNode;
          return;
       }


       Node<T>* temp = begin;

       while(temp != nullptr) {

           if (temp->data == data) {

               deletingNode = temp;
               temp->prev->next = temp->next;
               temp->next->prev = temp->prev;

               delete deletingNode;
               return;

           } else {
               temp = temp->next;
           }

       }


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

        while(node != nullptr) {

           qDebug() << node->data;
           node = node->prev;

        }

    };


    Node<T>* getBegin() {
        return begin;
    }

    Node<T>* getEnd() {
        return end;
    }

private:
    Node<T>* begin;
    Node<T>* end;
};

#endif // PRIORITYQUEUE_H
