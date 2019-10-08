#include <iostream>
#include <vector>
#include <algorithm>
#include "vector.hpp"
#include "bucket_sort.hpp"
#include <chrono>
#include <ratio>
#include <thread>

using duration_t = std::chrono::microseconds;

int main() {
    std::ios::sync_with_stdio(false);
    TVector<TData> bVect;
    std::vector<TData> qVect;
    TData in;
    
    while(std::cin >> in.key >> in.val) {
        bVect.PushBack(in);
        qVect.push_back(in);
    }

    std::chrono::time_point<std::chrono::system_clock> start, end;
    uint64_t bucket_time = 0;
    uint64_t quick_time = 0;
    
    start = std::chrono::system_clock::now();
    TVector<TData> res;
    res = BucketSort(bVect, bVect.Size());
    end = std::chrono::system_clock::now();
    bucket_time += std::chrono::duration_cast<duration_t>( end - start ).count();

    start = std::chrono::system_clock::now();
    std::sort(qVect.begin(), qVect.end(), [](TData a, TData b){
                                              return a.key > b.key;
                                          });
    end = std::chrono::system_clock::now();
    quick_time += std::chrono::duration_cast<duration_t>( end - start ).count();
    
    std::cout << "bucket ms=" << bucket_time << "\nquick ms=" << quick_time << std::endl;
    return 0;
} 
