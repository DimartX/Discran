#include "vector.hpp"
#include "bucket_sort.hpp"
#include <limits>
#include <iostream>

void InsertionSort(TVector<TData>& vect, int n) {
    for (int i = 1; i < n; i++) {
        TData now = vect[i];
        int j = i - 1;
        while(j >= 0 && vect[j].key > now.key) {
            vect[j + 1] = vect[j];
            --j;
        }
        vect[j + 1] = now;
    }
}

TVector<TData> BucketSort(TVector<TData> const& vect, int n) {
    TVector<TVector<TData> > buckets(n);

    uint64_t min_el = std::numeric_limits<int>::max();
    uint64_t max_el = std::numeric_limits<int>::min();

    for (int i = 0; i < n; i++) {
        TData elem = vect[i];
        min_el = std::min(min_el, elem.key);
        max_el = std::max(max_el, elem.key);
    }

    double len = (max_el - min_el + 1e-9);
            
    for (int i = 0; i < n; i++) {
        size_t num = ((vect[i].key - min_el) / len) * n;
        
        if (num >= (size_t)n)
            num = n - 1;
        
        buckets[num].PushBack(vect[i]);
        
    }
    
    for (int i = 0; i < n; i++) {
        InsertionSort(buckets[i], buckets[i].Size());
    }
    
    TVector<TData> res(n);
    int ind = 0;
    for (int i = 0; i < n; i++) {
        for (size_t j = 0; j < buckets[i].Size(); j++){
            res[ind++] = buckets[i][j];
        }
    }
    return res;
}
