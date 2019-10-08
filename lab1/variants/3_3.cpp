#include <iostream>
#include <cstdint>
#include <limits>
#include <cstdio>
#include <cmath>

struct TData{
    uint64_t key;
    uint64_t val;
};


template<class T>
class TVector {
private:
    size_t size_;
    size_t cap_;
    T *data_;
public:
    TVector() {
        size_ = 0;
        cap_ = 0;
        data_ = nullptr;
    };

    TVector(int n) {
        size_ = n;
        cap_ = n;
        data_ = new T[cap_];
    }

    TVector(int n, T x){
        size_ = n;
        cap_ = n;
        data_ = new T[cap_];
        for (size_t i = 0; i < size_; i++)
            data_[i] = x;
    }

    TVector(const TVector<T>& other){
        if (data_)
            delete[] data_;
        data_ = other.data_;
        size_ = other.size();
        cap_ = other.cap_;
    }
    
    ~TVector(){
        delete[] data_;
    }
    
    T& operator[] (const int id) const{
        return data_[id];
    }

    TVector<T>& operator= (const TVector<T>& other) {
        if (this != &other) {
            T* tmp = new T[other.size_];
            std::copy(other.data_, other.data_ + other.size_, tmp);
            delete[] data_;
            data_ = tmp;
            size_ = other.size_;
            cap_ = other.cap_;
        }
        return *this;
    }

    void PushBack(const T& newdata_) {
        if (cap_ == size_){
            cap_ *= 2;
            if (cap_ == 0)
                cap_ = 1;
            T *tmp = new T[cap_];
            for (size_t i = 0; i < size_; ++i) {
                tmp[i] = data_[i];
            }
            delete[] data_;
            data_ = tmp;
        }
        data_[size_++] = newdata_;
    }

    size_t size() const {
        return size_;
    }
};

TVector<TData> RadixSort(TVector<TData> const& vect, int n) {
    TVector<TData> elems;
    elems = vect;
    const uint32_t B = 64;
    const uint32_t R = std::min((int)log2(n), 16);
    
    uint64_t mask = 0;
    for (int i = 0; i < R; i++){
        mask <<= 1;
        mask += 1;
    }
    
    for (int g = 0; g < (B + R - 1) / R; g++){

        const int MAXN = 1 << R;
        TVector<int> count(MAXN+1, 0);
        for (size_t i = 0; i < elems.size(); i++){
            ++count[(elems[i].key & mask) >> (R * g)];
        }
        for (int i = 1; i <= MAXN; i++){
            count[i] += count[i-1];
        }    
        TVector<TData> res(elems.size());
        for (int i = elems.size()-1; i >= 0; --i){
            res[--count[(elems[i].key & mask) >> (R * g)]] = elems[i];
        }
        elems = res;

        mask <<= R;
    }
    return elems;
}

int main() {
    std::ios::sync_with_stdio(false);
    TData in;
    TVector<TData> vect{};

    while(std::cin >> in.key >> in.val) {
        vect.PushBack(in);
    }
     
    TVector<TData> res;
    if (vect.size() > 1)
        res = RadixSort(vect, vect.size());
    else
        res = vect;
    for (size_t i = 0; i < res.size(); i++) {
        std::cout << res[i].key << '\t' << res[i].val;
        std::cout << "\n";
    }
    return 0;
} 
