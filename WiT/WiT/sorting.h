#ifndef SORTING_H
#define SORTING_H
#include <vector>
#include "train.h"
#include "random.h"

template <typename T>
void _swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

int randomPivot(int size);

int partition(std::vector<QString> sortingSequence, std::vector<train>& arr, int first, int last);

void quicksort(std::vector<QString> sortingSequence, std::vector<train>& arr, int first, int last);

void countingSort(std::vector<QString> sortingSequence, std::vector<train> arr[], int size);

void countingSort(int* first, int* last);

#endif // SORTING_H
