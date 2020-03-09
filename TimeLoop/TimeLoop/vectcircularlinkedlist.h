#ifndef VECTCIRCULARLINKEDLIST_H
#define VECTCIRCULARLINKEDLIST_H
#include <vector>
#include "circularlinkedlist.h"



class vectCircularLinkedList
{
public:
    vectCircularLinkedList();
    vectCircularLinkedList(Station* station);

    void checkIndex(int k);

    Station* get(int k);
    void set(int k, Station* station);
    void insert(int k, Station* station);
    void remove(int k);
    void print();
    void push(Station* station);

private:
    std::vector<Station*> vect;
};

#endif // VECTCIRCULARLINKEDLIST_H
