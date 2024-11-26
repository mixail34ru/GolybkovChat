#ifndef TSAVEVECDATASTORAGE_H
#define TSAVEVECDATASTORAGE_H

#include "safe_ptr.h"

#include <vector>
#include <functional>

template<typename T>
class TSaveVecDataStorage
{
    wstd::safe_ptr<std::vector<T>> _storage;

public:
    using size_type = typename std::vector<T>::size_type;

    std::function<void(void)> dataChanged = [](){};
    std::function<void(void)> dataCleared = [](){};

    TSaveVecDataStorage() {}
    TSaveVecDataStorage(size_type reserve_size) {
        _storage->reserve(reserve_size);
    }

    ~TSaveVecDataStorage() {}

    /* Capacity */

    bool empty() const { return _storage->empty(); }
    size_type size() const { return _storage->size(); }
    size_type max_size() const { return _storage->max_size(); }
    void reserve(size_type new_cap) { _storage->reserve(new_cap); }
    size_type capacity() const { return _storage->capacity(); }

    /* Element access */

    T at(const size_type& index) { return _storage->at(index); }
    const T at(const size_type& index) const { return _storage->at(index); }

    void push_back(const T& package) {
        _storage->push_back(package);
        dataChanged();
    }

    void clear() {
        _storage->clear();
        dataCleared();
    }
}; //class TSaveVecDataStorage
//-------------------------------------------------------------------

#endif // TSAVEVECDATASTORAGE_H
