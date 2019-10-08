#include <iostream>
#include <cstdint>
#include <limits>
#include <cstdio>
#include <vector>

struct TData{
    uint16_t key;
    char val[65] = {'\0'};
};

std::vector<TData> bucket_sort(std::vector<TData>& elems, uint16_t maxn) {
    std::vector<uint32_t> count(maxn+1, 0);
    for (size_t i = 0; i < elems.size(); i++){
        ++count[elems[i].key];
    }    
    for (int i = 1; i <= maxn; i++){
        count[i] += count[i-1];
    }    
    std::vector<TData> res(elems.size());
    for (int i = elems.size()-1; i >= 0; --i){
        res[--count[elems[i].key]] = elems[i];
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    TData in;
    std::vector<TData> vect;

    uint16_t maxn = 0;
    while(std::cin >> in.key) {
        std::cin >> in.val;
        maxn = std::max(maxn, in.key);
        vect.push_back(in);
    }
    std::vector<TData> res;
    res = bucket_sort(vect, maxn);
    
    for (size_t i = 0; i < res.size(); i++) {
        std::cout << res[i].key << '\t' << res[i].val;
        std::cout << std::endl;
    }
    return 0;
} 
