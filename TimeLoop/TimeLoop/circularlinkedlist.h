#ifndef CIRCLEDLINKEDLIST_H
#define CIRCLEDLINKEDLIST_H
#include <vector>
#include <QString>
#include "functs.h"
#include "station.h"

struct Node {
    Station* station;
    Node* prev;
    Node* next;
};


class CircularLinkedList
{
public:
    CircularLinkedList();

    CircularLinkedList(Station* station);

    CircularLinkedList(std::vector<Station*> stations);

    Station* get(int k);

    Node* getNode(int k);

    void set(int k, Station* station);

    void push(Station* station);

    void insert(int k, Station* station);

    Node* remove(int k);

    void print();

    double getTime(QString fromSt, QString toSt);

    void changeStation(int k, Station* newStation);

    bool containsStName(QString stName);

    void checkIndex(int k);


    Node* start;
};

#endif // CIRCLEDLINKEDLIST_H
