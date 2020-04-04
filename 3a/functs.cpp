#include "functs.h"
#include <QDebug>
#include <QRegularExpression>
#include <random>
#include <algorithm>
#include <iterator>
#include <functional>
#include "sorting.h"


std::random_device device;
std::seed_seq seq{device(),(unsigned)time(nullptr)};
std::mt19937 generator(seq);

int getRandomInt(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}


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
