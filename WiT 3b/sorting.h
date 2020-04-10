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

void fillZeros(int* first, int size);

int partition(std::vector<QString> sortingSequence, std::vector<train>& arr, int first, int last);

void quicksort(std::vector<QString> sortingSequence, std::vector<train>& arr, int first, int last);

void countingSort(QString field, std::vector<train>& arr, std::vector<train>& temp, int first = 0, int last = -1);

void countingSortByDigit(QString field, std::vector<train>& arr, std::vector<train>& temp, int first = 0, int last = -1, int digit = 1);

void countingSortBySeq(std::vector<QString> sortingShortSeq, std::vector<train>& arr, std::vector<train>& temp);

void radixSort(QString field, std::vector<train>& arr, std::vector<train>& temp, int first = 0, int last = -1);

void radixSortBySeq(std::vector<QString> sortingShortSeq, std::vector<train>& arr, std::vector<train>& temp);

#endif // SORTING_H
