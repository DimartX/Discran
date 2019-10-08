#include <iostream>
#include <cstdint>
#include <limits>
#include <cstdio>

struct TData{
    uint16_t key;
    uint64_t val;
    TData(){}
    TData(const TData& cp){
        key = cp.key;
        val = cp.val;
    }
};

const int ADD_CAP = 128;

template<class T>
class TVector {
private:
    size_t size_;
    size_t cap_;
    T *data_;
public:
    TVector() {
        size_ = 0;
        cap_ = ADD_CAP;
        data_ = new T[cap_];
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
        data_ = new T[other.size()];
        size_ = other.size();
        cap_ = other.cap_;
        for (size_t i = 0; i < size_; i++)
            data_[i] = other[i];
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
            T *tmp = new T[cap_];
            for (size_t i = 0; i < size_; i++) {
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

TVector<TData> bucket_sort(TVector<TData> const& elems, int maxn) {
    TVector<int> count(maxn+1, 0);
    for (size_t i = 0; i < elems.size(); i++){
        ++count[elems[i].key];
    }    
    for (int i = 1; i <= maxn; i++){
        count[i] += count[i-1];
    }    
    TVector<TData> res(elems);
    for (int i = elems.size()-1; i >= 0; --i){
        res[--count[elems[i].key]] = elems[i];
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    TData in;
    TVector<TData> vect;

    uint16_t maxn = 0;
    while(std::cin >> in.key) {
        std::cin >> in.val;
        maxn = std::max(maxn, in.key);
        vect.PushBack(in);
    }
    TVector<TData> res;
    res = bucket_sort(vect, maxn);
    
    for (size_t i = 0; i < res.size(); i++) {
        std::cout << res[i].key << '\t' << res[i].val;
        std::cout << std::endl;
    } 
    return 0;
} 
