#ifndef SORTING_H
#define SORTING_H
#include <cstddef>
#include <QDebug>

template <class T>
void _swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
void selectionSort(T &arr, std::size_t n)
{
    unsigned int sorted_idx = 0,
        elem = 0,
        min_idx = 0;

    while(sorted_idx < n-1) {

        min_idx = sorted_idx;
        elem = sorted_idx + 1;

        while (elem < n) {

            if (arr[elem] < arr[min_idx]) {
                min_idx = elem;
            }

            elem++;
        }

        _swap(arr[min_idx], arr[sorted_idx]);

        sorted_idx++;
    }
}

template <class T>
T medianOfThree(T arr[], int first, int last)
{
    int med = (first+last)/2;

    int three[3] = {first, med, last};
    selectionSort(three, 3);

    return arr[three[1]];
}

template <class T>
int partition(T arr[], int first, int last)
{
    T pivot;
    pivot = medianOfThree(arr, first, last);

    int low = first-1, high = last+1;

    while (true) {

        do {
            low++;
        } while (arr[low] < pivot);

        do {
            high--;
        } while(arr[high] > pivot);

        if (low >= high)
            return high;

        _swap(arr[high], arr[low]);
    }
}

template <class T>
void quickSort(T arr[], int first, int last)
{
    if (first < last) {
        int partit = partition(arr, first, last);
        quickSort(arr, first, partit);
        quickSort(arr, partit+1, last);
    }
}

#endif // SORTING_H
