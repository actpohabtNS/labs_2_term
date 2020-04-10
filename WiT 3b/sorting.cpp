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

void fillZeros(int *first, int size)
{
    for (int i = 0; i < size; i++)
    {
        first[i] = 0;
    }
}

void countingSort(QString field, std::vector<train>& arr, std::vector<train>& temp, int first, int last)
{
    if (last == -1) last = arr.size()-1;

    int min = getMinShortByField(field, arr, first, last);
    int max = getMaxShortByField(field, arr, first, last);

    int idx_size = max - min + 1;

    int* indexes = new int[idx_size];
    fillZeros(indexes, idx_size);

    for (int elem = 0; elem + first <= last; elem++)
    {
        indexes[arr[elem+first].getShort(field) - min]++;
    }

    int indexesSum = 0;

    for (int idx = 0; idx < idx_size; idx++)
    {
        indexesSum += indexes[idx];
        indexes[idx] = indexesSum;
    }

    std::copy(arr.begin() + first, arr.begin() + last + 1, temp.begin());

    for (int elem = last - first; elem >= 0; elem--)
    {
        arr[first + indexes[temp[elem].getShort(field) - min] - 1] = temp[elem];
        indexes[temp[elem].getShort(field)-min]--;
    }

}

void countingSortBySeq(std::vector<QString> sortingShortSeq, std::vector<train> &arr, std::vector<train> &temp)
{
    countingSort(sortingShortSeq[0], arr, temp);

    if (sortingShortSeq.size() < 2) return;

    int chainLength = 1;
    int firstSameValueIdx = 0;

    for (unsigned int idx = 1; idx < arr.size(); idx++)
    {
        if (arr[firstSameValueIdx].getShort(sortingShortSeq[0]) == arr[idx].getShort(sortingShortSeq[0]))
        {
            chainLength++;
        }
        else
        {
            firstSameValueIdx = idx;
            if (chainLength != 1)
            {
                countingSort(sortingShortSeq[1], arr, temp, idx - chainLength, idx-1);
            }

            chainLength = 1;
        }
    }

    if (chainLength != 1)
    {
        countingSort(sortingShortSeq[1], arr, temp, arr.size() - chainLength, arr.size()-1);
    }
}

void countingSortByDigit(QString field, std::vector<train> &arr, std::vector<train> &temp, int first, int last, int digit)
{
    if (last == -1) last = arr.size()-1;

    int idx_size = 10;

    int* indexes = new int[idx_size];
    fillZeros(indexes, idx_size);

    for (int elem = 0; elem + first <= last; elem++)
    {
        indexes[(arr[elem+first].getShort(field)/digit)%10]++;
    }

    int indexesSum = 0;

    for (int idx = 0; idx < idx_size; idx++)
    {
        indexesSum += indexes[idx];
        indexes[idx] = indexesSum;
    }

    std::copy(arr.begin() + first, arr.begin() + last + 1, temp.begin());

    for (int elem = last - first; elem >= 0; elem--)
    {
        arr[first + indexes[(temp[elem].getShort(field)/digit)%10] - 1] = temp[elem];
        indexes[(temp[elem].getShort(field)/digit)%10]--;
    }
}

void radixSort(QString field, std::vector<train> &arr, std::vector<train> &temp, int first, int last)
{
    int max = getMaxShortByField(field, arr, first, last);

    for (int digit = 1; max/digit > 0; digit *= 10)
    {
        countingSortByDigit(field, arr, temp, first, last, digit);
    }
}

void radixSortBySeq(std::vector<QString> sortingShortSeq, std::vector<train> &arr, std::vector<train> &temp)
{
    radixSort(sortingShortSeq[0], arr, temp);

    if (sortingShortSeq.size() < 2) return;

    int chainLength = 1;
    int firstSameValueIdx = 0;

    for (unsigned int idx = 1; idx < arr.size(); idx++)
    {
        if (arr[firstSameValueIdx].getShort(sortingShortSeq[0]) == arr[idx].getShort(sortingShortSeq[0]))
        {
            chainLength++;
        }
        else
        {
            firstSameValueIdx = idx;
            if (chainLength != 1)
            {
                radixSort(sortingShortSeq[1], arr, temp, idx - chainLength, idx-1);
            }

            chainLength = 1;
        }
    }

    if (chainLength != 1)
    {
        radixSort(sortingShortSeq[1], arr, temp, arr.size() - chainLength, arr.size()-1);
    }
}
