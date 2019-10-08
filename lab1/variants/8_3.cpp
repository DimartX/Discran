#include <iostream>
#include <cstdint>
#include <limits>
#include <cstdio>

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

inline void InsertionSort(TVector<TData> const& vect, int n) {
    for (int i = 1; i < n; ++i) {
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

    uint64_t min_el = vect[0].key;
    uint64_t max_el = vect[0].key;
    for (int i = 0; i < n; ++i) {
        TData elem = vect[i];
        min_el = std::min(min_el, elem.key);
        max_el = std::max(max_el, elem.key);
    }

    double len = (max_el - min_el + 1e-9);
    
    for (int i = 0; i < n; ++i) {
        size_t num = ((vect[i].key - min_el) / len) * n;
        if (num >= (size_t)n)
            num = n - 1;
        buckets[num].PushBack(vect[i]);
    }
    
    for (int i = 0; i < n; ++i) {
        InsertionSort(buckets[i], buckets[i].size());
    }
        
    TVector<TData> res(n);
    int ind = 0;
    for (int i = 0; i < n; ++i) {
        for (size_t j = 0; j < buckets[i].size(); ++j){
            res[ind++] = buckets[i][j];
        }
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    TData in;
    TVector<TData> vect{};

    while(std::cin >> in.key >> in.val) {
        vect.PushBack(in);
    }
     
    TVector<TData> res;
    if (vect.size() > 0)
        res = BucketSort(vect, vect.size());
    
    for (size_t i = 0; i < res.size(); ++i) {
        std::cout << res[i].key << '\t' << res[i].val;
        std::cout << "\n";
    }
    return 0;
} 
