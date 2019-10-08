#include <iostream>
#include <cstdint>
#include <limits>
#include <cstdio>
#include <vector>
#include <string>

struct TData{
    uint32_t key;
    char val[65] = {'\0'};
};

const int MAXN = 1000000;

std::vector<TData> bucket_sort(std::vector<TData>& elems) {
    uint32_t count[MAXN] = {0};
    for (size_t i = 0; i < elems.size(); i++){
        ++count[elems[i].key];
    }

    for (int i = 1; i <= MAXN; i++){
        count[i] += count[i-1];
    }

    std::vector<TData> res(elems.size());
    for (int i = elems.size()-1; i >= 0; --i){
        res[--count[elems[i].key]] = elems[i];
    }
    

    return res;
}

uint32_t StrToInt(char *str){
    uint64_t tmp = 0;
    for (int i = 0; i < 6; i++){
        tmp = tmp * 10 + ((int)str[i] - 48);
    }
    return tmp;
}

char* IntToStr(int num){
    char* tmp = new char[6];
    for (int i = 5; i >= 0; i--){
        tmp[i] = (char)(48 + num % 10);
        num /= 10;
    }
    return tmp;
}

int main() {
    std::ios::sync_with_stdio(false);
    TData in;
    std::vector<TData> vect;

    char str_in[6];
    while(std::cin >> str_in) {
        in.key = StrToInt(str_in);
        std::cin >> in.val;
        vect.push_back(in);
    }

    std::vector<TData> res;
    res = bucket_sort(vect);
    
    for (size_t i = 0; i < res.size(); i++) {
        std::cout << IntToStr(res[i].key) << '\t' << res[i].val;
        std::cout << std::endl;
    }
    return 0;
} 
