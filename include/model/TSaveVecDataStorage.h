#ifndef TSAVEVECDATASTORAGE_H
#define TSAVEVECDATASTORAGE_H

#include "TPackageFormat.h"
#include "safe_ptr.h"

#include <vector>
#include <functional>

template<typename T>
class TSaveVecDataStorage
{
    using size_type = std::vector<int>::size_type;

    wstd::safe_ptr<std::vector<T>> _storage;

public:
    std::function<void(void)> dataChanged = [](){};
    std::function<void(void)> dataCleared = [](){};

    TSaveVecDataStorage() {}
    TSaveVecDataStorage(size_t reserve_size) {
        _storage->reserve(reserve_size);
    }

    ~TSaveVecDataStorage() {}

    /* Capacity */

    bool empty() const { return _storage->empty(); }
    size_t size() const { return _storage->size(); }
    size_t max_size() const { return _storage->max_size(); }
    void reserve(size_type new_cap) { _storage->reserve(new_cap); }
    size_t capacity() const { return _storage->capacity(); }

    /* Element access */

    T at(const size_type& index) { return _storage->at(index); }
    const T at(const size_type& index) const { return _storage->at(index); }

    void push_back(const Package& package) {
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
