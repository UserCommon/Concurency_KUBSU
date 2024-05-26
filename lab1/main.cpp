#define S 100000
#define N 16

#include <iostream>
#include <omp.h>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <chrono>

// С параллелизмоом
auto bubbleSortParallelized(std::vector<int>& arr) -> void {
    for(int i = 0; i < arr.size() - 1; i++) {
        #pragma omp parallel for
        for(int j = 0; j < arr.size() - i - 1; j++) {
            if(arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j+1]);
        }
    }
}

// Без параллелизма
auto bubbleSortSyncronous(std::vector<int>& arr) -> void {
    for(int i = 0; i < arr.size() - 1; i++) {
        for(int j = 0; j < arr.size() - i - 1; j++) {
            if(arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j+1]);
        }
    }
}

template<typename F, typename A>
auto measureFunction(F funciton, std::vector<A>& input) {
    auto start = std::chrono::high_resolution_clock::now();
    funciton(input);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
}

auto main() -> int {
    omp_set_num_threads(N);
    std::random_device rnd_device;
    std::mt19937 mersenne_engine {rnd_device()};
    std::uniform_int_distribution<int> dist {1, 3510};

    auto gen = [&dist, &mersenne_engine](){
                   return dist(mersenne_engine);
               };

    std::vector<int> vecParallel(S);
    generate(std::begin(vecParallel), std::end(vecParallel), gen);

    std::vector<int> vecSyncronous(S);
    generate(std::begin(vecSyncronous), std::end(vecSyncronous), gen);

    std::cout << "Benchmarking parallelized version..." << std::endl;
    std::cout << "Result: "
              << measureFunction(bubbleSortParallelized, vecParallel)
              << " ms."
              << std::endl;

    std::cout << "Benchmarking syncronous version..." << std::endl;
    std::cout << "Result: "
              << measureFunction(bubbleSortSyncronous, vecSyncronous)
              << " ms."
              << std::endl;
    return 0;
}
