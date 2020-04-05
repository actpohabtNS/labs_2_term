#include "functs.h"
#include <QDebug>
#include "sorting.h"

int* createRandomIntArray(int size, int from, int to)
{
    int* arr = new int[size];

    if (to == -1) to = size-1;

    for (int i = 0; i < size; i++) {
        arr[i] = getRandomInt(from, to);
    }

    return arr;
}

int* createSortedIntArray(int size, bool ascending)
{
    int* arr = new int[size];

    int elem = (ascending ? 1 : size);

    for (int elem_idx = 0; elem_idx < size; elem_idx++)
    {
        arr[elem_idx] = elem;

        elem = elem + (ascending ? 1 : -1);
    }

    return arr;
}

int* almostSortedIntArray(int size, bool ascending)
{
    int* arr = createSortedIntArray(size, ascending);

    for (int i = 0; i < size/10; i++) {
        int idx1 = getRandomInt(0, size-1), idx2 = getRandomInt(0, size-1);
        _swap(arr[idx1], arr[idx2]);
    }

    return arr;
}
