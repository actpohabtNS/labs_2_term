#include "arrcilcularlinkedlist.h"
#include <stdexcept>
#include <QtDebug>

arrCilcularLinkedList::arrCilcularLinkedList()
{
    start = new Station*[0];
    size = 0;
}

arrCilcularLinkedList::arrCilcularLinkedList(Station *station)
{
    start = new Station*[1];
    start[0] = station;
    size = 1;
}

int arrCilcularLinkedList::getSize()
{
    return size;
}

Station* arrCilcularLinkedList::get(int k)
{
    checkIndex(k);
    return start[(k-1) % size];
}

void arrCilcularLinkedList::set(int k, Station *station)
{
    checkIndex(k);
    start[(k-1) % size] = station;
}

void arrCilcularLinkedList::insert(int k, Station *station)
{
    checkIndex(k);

    if(size == 0) {

        start = new Station*[1];
        start[0] = station;

        size = 1;
        return;

    }

    k = (k-1)%size;

    Station** temp = new Station*[size+1];
    std::copy(start, start + k, temp);
    temp[k] = station;
    std::copy(start + k, start + size, temp + k+1);
    delete [] start;

    start = temp;
    size++;
}

void arrCilcularLinkedList::remove(int k)
{
    checkIndex(k);

    if (size == 0) return;

    k = (k-1)%size;

    Station** temp = new Station*[size-1];
    std::copy(start, start + k, temp);
    delete start[k];
    std::copy(start + k+1, start + size, temp + k);
    delete [] start;

    start = temp;
    size--;
}

void arrCilcularLinkedList::print()
{
    for (unsigned int i = 0; i < size; i++) {
        qDebug() << start[i]->name << start[i]->timeNext;
    }
}

void arrCilcularLinkedList::push(Station *station)
{
    Station** temp = new Station*[size+1];
    std::copy(start, start + size, temp);
    delete [] start;

    start = temp;
    start[size] = station;
    size++;
}

void arrCilcularLinkedList::checkIndex(int index)
{
    if (index <= 0) {
        throw std::range_error("K [1, Inf] is out of range: " + std::to_string(index));
    }
}
