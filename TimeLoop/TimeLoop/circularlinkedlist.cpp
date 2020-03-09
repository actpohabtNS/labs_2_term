#include "circularlinkedlist.h"
#include "functs.h"
#include <stdexcept>
#include <QtDebug>

CircularLinkedList::CircularLinkedList()
{
    start = nullptr;
}

CircularLinkedList::CircularLinkedList(Station* station)
{
    Node* startNode = new Node{station, nullptr, nullptr};
    startNode->prev = startNode;
    startNode->next = startNode;
    start = startNode;
}

CircularLinkedList::CircularLinkedList(std::vector<Station*> stations)
{
    Node* startNode = new Node{stations[0], nullptr, nullptr};
    startNode->prev = startNode;
    startNode->next = startNode;

    start = startNode;

    for (unsigned int i = 1; i < stations.size(); i++) {

        push(stations[i]);

    }

}

Station* CircularLinkedList::get(int k)
{
    checkIndex(k);

    Node* resNode = start;

    for (int i = 1; i < k; i++) {
        Node* temp = resNode->next;
        resNode = temp;
    }


    return resNode->station;
}

Node* CircularLinkedList::getNode(int k)
{
    checkIndex(k);

    Node* resNode = start;

    for (int i = 1; i < k; i++) {
        Node* temp = resNode->next;
        resNode = temp;
    }


    return resNode;
}

void CircularLinkedList::set(int k, Station *station)
{
    checkIndex(k);

    Node* resNode = start;

    for (int i = 1; i < k; i++) {
        Node* temp = resNode->next;
        resNode = temp;
    }

    resNode->station = station;
}

void CircularLinkedList::push(Station *station)
{
    if (start == nullptr) {

        Node* startNode = new Node{station, nullptr, nullptr};
        startNode->prev = startNode;
        startNode->next = startNode;

        start = startNode;

    } else {

        Node* pushNode = new Node{station, start->prev, start};

        start->prev->next = pushNode;
        start->prev = pushNode;

    }
}

void CircularLinkedList::insert(int k, Station *station)
{
    if (start == nullptr) {
        Node* startNode = new Node{station, nullptr, nullptr};
        startNode->prev = startNode;
        startNode->next = startNode;

        start = startNode;

    } else {

        Node* befNode = getNode(k);

        Node* insertNode = new Node{station, befNode->prev, befNode};

        befNode->prev->next = insertNode;
        befNode->prev = insertNode;

        if (befNode == start) start = insertNode;

    }
}

Node *CircularLinkedList::remove(int k)
{
    if (start == nullptr) return nullptr;

    if (start == start->next) {

        Node* temp = start;
        start = nullptr;
        return temp;

    } else {

        Node* delNode = getNode(k);

        if (delNode == start) start = delNode->next;

        delNode->prev->next = delNode->next;
        delNode->next->prev = delNode->prev;

        return delNode;

    }
}

void CircularLinkedList::print()
{
    Node* temp = start;

    do {
        qDebug() << temp->station->name;
        temp = temp->next;
    } while (temp != start);

}

double CircularLinkedList::getTime(QString fromSt, QString toSt)
{

    if (fromSt == toSt) return 0;

    double dur1 = 0, dur2 = 0, tempDur = 0;

    Node* node = start;

    do {

        if ((node->station->name == fromSt || node->station->name == toSt ) && dur1 == 0) {
            dur1 += tempDur;
            tempDur = 0;
        }

        if ((node->station->name == fromSt || node->station->name == toSt ) && dur1 != 0) {
            dur2 += tempDur;
            tempDur = 0;
        }

        tempDur += node->station->timeNext;

        node = node->next;

    } while (node != start);

    if (dur2 == 0) dur2 += tempDur; // if keyStation == start, dur1 is NOT being split by start => dur1 = lineDur, dur2 = 0
    else dur1 += tempDur;           // normal

    return __min(dur1, dur2);

}

void CircularLinkedList::changeStation(int k, Station *newStation)
{

    if (start == nullptr) return;

    Node* oldNode = getNode(k);

    oldNode->station = newStation;

}

bool CircularLinkedList::containsStName(QString stName)
{

    bool contains = false;

    if (start == nullptr) return false;

    Node* node = start;

    do {

        if (node->station->name.toLower() == stName.toLower()) contains = true;

        node = node->next;

    } while (node != start);

    return contains;

}

void CircularLinkedList::checkIndex(int k)
{
    if (k <= 0 ) {
        throw std::range_error("K [1, Inf] is out of range: " + std::to_string(k));
    }
}

