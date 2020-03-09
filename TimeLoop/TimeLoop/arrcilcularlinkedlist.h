#ifndef ARRCILCULARLINKEDLIST_H
#define ARRCILCULARLINKEDLIST_H
#include "circularlinkedlist.h"


class arrCilcularLinkedList
{
public:
    arrCilcularLinkedList();
    arrCilcularLinkedList(Station* station);

    int getSize();

    Station* get(int k);
    void set(int k, Station* station);
    void insert(int k, Station* station);
    void remove(int k);
    void print();
    void push(Station* station);


private:
    unsigned int size;
    Station** start;

    void checkIndex(int index);
};

#endif // ARRCILCULARLINKEDLIST_H
