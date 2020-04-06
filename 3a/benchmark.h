#ifndef BENCHMARK_H
#define BENCHMARK_H
#include <vector>
#include <chrono>
#include "date.h"

template <class ...Types>
unsigned long long benchSortAlg(void sort(Types ...Args), Types ...Args)
{
    auto start = std::chrono::high_resolution_clock::now();
// ==========================================================

    sort(Args...);

// ==========================================================
    auto stop = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    return dur.count();
}


#endif // BENCHMARK_H
