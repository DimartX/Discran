#include <iostream>
#include "vector.hpp"
#include "bucket_sort.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    TVector<TData> vect;
    TData in;
    
    while(std::cin >> in.key >> in.val) {
        vect.PushBack(in);
    }

    TVector<TData> res;
    res = BucketSort(vect, vect.Size());
    
    for (size_t i = 0; i < res.Size(); i++) {
        std::cout << res[i].key << '\t' << res[i].val << "\n";
    }
    return 0;
} 
