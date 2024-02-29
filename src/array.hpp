#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <sstream>
#include <utility>
#include <iomanip>

template <typename T>
class Array {
public:
    // Implement all methods from int_array.hpp here

    // Construct zero-length array.
    Array() : len(0), buf(nullptr) {}

    // Construct array of given length.
    explicit Array(int len) : len(len), buf(new T[len]) {}

     // Copy constructor
    Array(const Array& other) : len(other.len), buf(new T[other.len]) {
        std::copy(other.buf, other.buf + other.len, buf);
    }

    // Move constructor
    Array(Array&& other) noexcept : len(other.len), buf(other.buf) {
        other.len = 0;
        other.buf = nullptr;
    }

    void swap(Array<T>& lhs, Array<T>& rhs) noexcept {
        std::swap(lhs.len, rhs.len);
        std::swap(lhs.buf, rhs.buf);
    }

    Array& operator=(Array other) noexcept {
        swap(*this, other);
        return *this;
    }

    ~Array() {
        delete[] buf;
    }

    int length() const {
        return len;
    }

    T& operator[](int index) {
        if (!in_bounds(index)) {
            throw std::out_of_range("Exception operator[](" + std::to_string(index) + ") Out Of Range");
        }
        return buf[index];
    }

    const T& operator[](int index) const {
        if (!in_bounds(index)) {
            throw std::out_of_range("Exception operator[](" + std::to_string(index) + ") Out Of Range");
        }
        return buf[index];
    }

    void fill(const T& val) {
        std::fill_n(buf, len, val);
    }

    template <typename Fn>
    void fill_with_fn(Fn fn){
        for (int i = 0; i < len; ++i) {
            buf[i] = fn(i); 
        }
    }

private:
    int len;
    T* buf;

    bool in_bounds(int index) const {
        return index >= 0 && index < len;
    }
};

template <typename T>
// Implementation of the free-standing operator<<
std::ostream& operator<<(std::ostream& out, const Array<T>& array) {
    std::ostringstream temp;
    temp << std::setprecision(2) << std::fixed << std::right;
    for (int i = 0; i < array.length(); ++i) {
        temp << std::setw(8) << array[i];
    }
    out << temp.str();
    return out;
}

template <typename T>
// Implementation of the free-standing operator>>
std::istream& operator>>(std::istream& in, Array<T>& array) {
    for (int i = 0; i < array.length(); ++i) {
        in >> array[i];
    }
    return in;
}
#endif // ARRAY_HPP
