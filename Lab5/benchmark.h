#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <vector>
#include <chrono>

template <typename ReturnType, typename Func, class ...Types>
std::pair<unsigned long long, ReturnType> benchAlg(Func alg, Types ...Args)
{
    std::pair<unsigned long long, ReturnType> res;

    auto start = std::chrono::high_resolution_clock::now();
// ==========================================================

    res.second = alg(Args...);

// ==========================================================
    auto stop = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    res.first = dur.count();

    return res;
}

#endif // BENCHMARK_H
