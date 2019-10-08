#pragma once

#include "vector.hpp"
#include <cstdint>

struct TData{
    uint64_t key;
    char val[66] = {'\0'};
};

void InsertionSort(TVector<TData> const& , int );

TVector<TData> BucketSort(TVector<TData> const& , int );
