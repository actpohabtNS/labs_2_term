#include "sorting.h"

int randomPivot(int size)
{
    return getRandomInt(0, size-1);
}

int partition(std::vector<QString> sortingSequence, std::vector<train>& arr, int first, int last)
{
    int pivotIdx = randomPivot(last+1);
    int low = first-1, high = last+1;

    while (true) {

        do {
            low++;

        } while (sequenceGreater(sortingSequence, arr[pivotIdx], arr[low]));

        do {
            high--;

        } while(sequenceGreater(sortingSequence, arr[high], arr[pivotIdx]));

        if (low >= high)
        {
           return high;
        }


        _swap(arr[high], arr[low]);
    }
}

void quicksort(std::vector<QString> sortingSequence, std::vector<train>& arr, int first, int last)
{
    if (first >= last) return;

    int pivot_idx = partition(sortingSequence, arr, first, last);
    quicksort(sortingSequence, arr, first, pivot_idx);
    quicksort(sortingSequence, arr, pivot_idx+1, last);
}

void countingSort(int *first, int *last)
{

}
