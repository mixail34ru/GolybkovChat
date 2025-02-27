#ifndef TVECSTORAGE_H
#define TVECSTORAGE_H

#include <vector>
#include <functional>


template<typename T>
class TVecStorage
{
public:
    using size_type = typename std::vector<T>::size_type;

    std::function<void(void)> dataChanged = [](){};
    std::function<void(void)> dataCleared = [](){};

    std::function<void(int, int)> inserted = [](int i, int count){};
    std::function<void(int, int)> erased = [](int i, int count){};

    TVecStorage() {}
    TVecStorage(size_type reserve_size) {
        _storage.reserve(reserve_size);
    }

    virtual ~TVecStorage() {}

    /* Capacity */

    bool empty() const noexcept { return _storage.empty(); }
    size_type size() const noexcept { return _storage.size(); }
    size_type max_size() const noexcept { return _storage.max_size(); }
    void reserve(size_type new_cap) { _storage.reserve(new_cap); }
    size_type capacity() const noexcept { return _storage.capacity(); }

    /* Element access */

    T at(const size_type& index) { return _storage.at(index); }
    const T at(const size_type& index) const { return _storage.at(index); }
    T* data() noexcept { return _storage.data(); }
    const T* data() const noexcept { return _storage.data(); }

    void push_back(const T& package) {
        _storage.push_back(package);
        dataChanged();
    }

    void erase(int index) {
        if (index < _storage.size()) {
            _storage.erase(_storage.begin() + index);
            dataChanged();
        }
    }

    void clear() noexcept {
        _storage.clear();
        dataCleared();
    }

private:
    std::vector<T> _storage;

}; //class TVecStorage
//-------------------------------------------------------------------

#endif // TVECSTORAGE_H
