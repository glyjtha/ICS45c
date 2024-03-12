#ifndef MAP_ARRAY_HPP
#define MAP_ARRAY_HPP

#include <algorithm>
#include <iterator>
#include <ranges>
#include <utility>
#include <vector>

template <typename Key, typename Value>
class MapArray {
public:
    class ArrayIterator {
    public:
        // Iterator traits:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = std::pair<Key, Value>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit ArrayIterator(std::pair<Key, Value>* ptr = nullptr) : ptr(ptr) {}

        ArrayIterator& operator++(){
            ++ptr;
            return *this;
        }

        ArrayIterator& operator--(){
            --ptr;
            return *this;
        }

        ArrayIterator operator++(int){
            ArrayIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        ArrayIterator operator--(int){
            ArrayIterator tmp = *this;
            --(*this);
            return tmp;
        }

        ArrayIterator& operator+=(difference_type d){
            ptr += d;
            return *this;
        }

        ArrayIterator& operator-=(difference_type d){
            ptr -= d;
            return *this;
        }

        friend ArrayIterator operator+(ArrayIterator it, difference_type d){
            return ArrayIterator(it.ptr + d);
        }

        friend ArrayIterator operator+(difference_type d, ArrayIterator it){
            return ArrayIterator(it.ptr + d);
        }

        friend ArrayIterator operator-(ArrayIterator it, difference_type d){
            return ArrayIterator(it.ptr - d);
        }

        friend difference_type operator-(ArrayIterator lhs, ArrayIterator rhs){
            return lhs.ptr - rhs.ptr;
        }

        bool operator==(const ArrayIterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const ArrayIterator& other) const {
            return ptr != other.ptr;
        }

        bool operator<(const ArrayIterator& other) const {
            return ptr < other.ptr;
        }

        bool operator<=(const ArrayIterator& other) const {
            return ptr <= other.ptr;
        }

        bool operator>(const ArrayIterator& other) const {
            return ptr > other.ptr;
        }

        bool operator>=(const ArrayIterator& other) const {
            return ptr >= other.ptr;
        }

        std::pair<Key, Value>& operator*() const{
            return *ptr;
        }
        std::pair<Key, Value>* operator->() const{
            return ptr;
        }
        std::pair<Key, Value>& operator[](difference_type d) const{
            return *(ptr + d);
        }

    private:
        std::pair<Key, Value>* ptr;
    };

    using value_type = std::pair<Key, Value>;
    using iterator = ArrayIterator;
    // Normally there would also be a const_iterator

    ArrayIterator begin(){
        return ArrayIterator(data.data());
    }
    ArrayIterator end(){
        return ArrayIterator(data.data()+data.size());
    }
    Value& operator[](const Key& key){
        auto it = std::lower_bound(data.begin(), data.end(), key,
        [](const value_type& a, const Key& k) { return a.first < k; });

        if (it != data.end() && !(key < it->first)) {
            return it->second;
        }

        return data.emplace(it, key, Value())->second;
    }

private:
    std::vector<std::pair<Key, Value>> data;
};


#endif // MAP_ARRAY_HPP
