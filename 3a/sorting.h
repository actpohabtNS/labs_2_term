#ifndef SORTING_H
#define SORTING_H
#include <cstddef>
#include <chrono>
#include <QDebug>
#include "random.h"

template <typename T>
void _swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
void shuffle(T arr[], int size)
{
    for (int i = size-1; i > 0; i--)
    {
        int j = getRandomInt(0,i);
        _swap(arr[i], arr[j]);
    }
}

template <typename T>
void selectionSort(T arr[], int first, int last)
{
    int sorted_idx = first,
        elem = first,
        min_idx = first;

    while(sorted_idx < last)
    {
        min_idx = sorted_idx;
        elem = sorted_idx + 1;

        while (elem < last+1)
        {
            if (arr[elem] < arr[min_idx])
            {
                min_idx = elem;
            }

            elem++;
        }

        _swap(arr[min_idx], arr[sorted_idx]);

        sorted_idx++;
    }
}

template <typename T>
T medianOfThree(T arr[], int first, int last)
{
    int med = (first+last)/2;

    int pivot = first;

    if ((arr[first] < arr[med] && arr[med] < arr[last]) ||
        (arr[last] < arr[med] && arr[med] < arr[first]))
    {
        pivot = med;

    } else if ((arr[first] < arr[last] && arr[last] < arr[med]) ||
               (arr[med] < arr[last] && arr[last] < arr[first]))
    {
        pivot = last;
    }

    return arr[pivot];
}

template <typename T>
int partition(T arr[], int first, int last)
{
    T pivot = medianOfThree(arr, first, last);
    int low = first-1, high = last+1;

    while (true) {

        do {
            low++;
        } while (arr[low] < pivot);

        do {
            high--;
        } while(arr[high] > pivot);

        if (low >= high)
        {
           return high;
        }


        _swap(arr[high], arr[low]);
    }
}

template <typename T>
void quicksort(T arr[], int first, int last)
{
    if (first >= last) return;

    int pivot_idx = partition(arr, first, last);
    quicksort(arr, first, pivot_idx);
    quicksort(arr, pivot_idx+1, last);
}

template <typename T>
T min(T a, T b)
{
    return (a < b ? a : b);
}

template <typename T>
void merge(T arr[], int from, int mid, int to)
{
    T temp[to-from];

    int temp_idx = 0, first_idx = from, second_idx = mid+1;

    while(first_idx <= mid && second_idx <= to) {

        if (arr[first_idx] <= arr[second_idx]) {
            temp[temp_idx++] = arr[first_idx++];
        } else {
            temp[temp_idx++] = arr[second_idx++];
        }

    }

    while(first_idx <= mid) {
        temp[temp_idx++] = arr[first_idx++];
    }

    while(second_idx <= to) {
        temp[temp_idx++] = arr[second_idx++];
    }

    for (int arr_idx = from, temp_idx = 0; arr_idx <= to; arr_idx++, temp_idx++) {
        arr[arr_idx] = temp[temp_idx];
    }

}

template <typename T>
void mergesort(T arr[], int n)
{

    for (int curr_size = 1; curr_size <= n-1; curr_size *= 2)
        {
            for (int left_start = 0; left_start < n-1; left_start += 2*curr_size)
            {
                int from = left_start;
                int mid = min(left_start + curr_size - 1, n-1);
                int to = min(left_start + 2*curr_size - 1, n-1);

                //qDebug() << curr_size << left_start;

                merge(arr, from, mid, to);
            }
        }
}

template <typename T>
void hybridQuicksort(T arr[], int first, int last, int step)
{
    if (first >= last) return;

    if (last - first < step) {

        selectionSort(arr, first, last);

    } else {

        int pivot_idx = partition(arr, first, last);
        hybridQuicksort(arr, first, pivot_idx, step);
        hybridQuicksort(arr, pivot_idx+1, last, step);

    }

}



#endif // SORTING_H
