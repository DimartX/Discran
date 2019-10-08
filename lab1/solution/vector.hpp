#pragma once

#include <cstdio>

template<class T>
class TVector {
private:
    size_t size_;
    size_t cap_;
    T *data_;
public:
    TVector() : 
        size_(0), cap_(0), data_(nullptr) {};

    TVector(int n) : 
        size_(n), cap_(n), data_(new T[cap_]) {};

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
        data_ = new T[other.cap_];
        for (size_t i = 0; i < other.size_; ++i) {
            data_[i] = other.data_[i];
        }
        size_ = other.Size();
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
            for (size_t i = 0; i < other.size_; ++i) {
                tmp[i] = other.data_[i];
            }
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

    size_t Size() const {
        return size_;
    }
};
