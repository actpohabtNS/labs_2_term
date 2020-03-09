#include "vectcircularlinkedlist.h"
#include <QtDebug>
#include <stdexcept>

vectCircularLinkedList::vectCircularLinkedList()
{
    vect = {};
}

vectCircularLinkedList::vectCircularLinkedList(Station* station)
{
    vect = {station};
}

void vectCircularLinkedList::checkIndex(int k)
{
    if (k <= 0 ) {
        throw std::range_error("K [1, Inf] is out of range: " + std::to_string(k));
    }
}

Station* vectCircularLinkedList::get(int k)
{

    checkIndex(k);

    if (vect.empty()) return nullptr;

    //if (vect.size() == 1) return vect[0];

    return vect[(k-1) % vect.size()];
}

void vectCircularLinkedList::set(int k, Station* station)
{
    checkIndex(k);

    if (vect.empty()) return;

    //if (vect.size() == 1) return vect[0];

    vect[(k-1) % vect.size()] = station;
}

void vectCircularLinkedList::insert(int k, Station* station)
{

    checkIndex(k);

    if (vect.empty()) {
        vect = {station};
        return;
    }

    vect.insert(vect.begin() + ((k-1) % vect.size()), station);
}

void vectCircularLinkedList::remove(int k)
{
    checkIndex(k);

    if (vect.empty()) return;

    vect.erase(vect.begin() + (k % vect.size()));
}

void vectCircularLinkedList::print()
{
    for (Station* station : vect) {
        qDebug() << station->name << station->timeNext;
    }
}

void vectCircularLinkedList::push(Station* station)
{
    vect.push_back(station);
}

