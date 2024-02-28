#ifndef INT_ARRAY_HPP
#define INT_ARRAY_HPP

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <utility>

class Array {
public:
    // Construct zero-length array.
    Array() : len(0), buf(nullptr) {}

    // Construct array of given length.
    explicit Array(int len) : len(len), buf(new int[len]) {}

    // Copy constructor
    Array(const Array& other) : len(other.len), buf(new int[other.len]) {
        std::copy(other.buf, other.buf + other.len, buf);
    }

    // Move constructor
    Array(Array&& other) noexcept : len(other.len), buf(other.buf) {
        other.len = 0;
        other.buf = nullptr;
    }

    // Swap two arrays (without allocations).
    friend void swap(Array& lhs, Array& rhs) noexcept {
        std::swap(lhs.len, rhs.len);
        std::swap(lhs.buf, rhs.buf);
    }

    // Copy assignment
    Array& operator=(Array other) noexcept {
        swap(*this, other);
        return *this;
    }

    // Destructor
    ~Array() {
        delete[] buf;
    }

    // Get the length of the array.
    int length() const {
        return len;
    }

    // Get a particular element of the array
    // with bounds check.
    int& operator[](int index) {
        if (!in_bounds(index)) {
            throw std::out_of_range("Exception operator[](" + std::to_string(index) + ") Out Of Range");
        }
        return buf[index];
    }

    // Get a particular element of the array (const version)
    // with bounds check.
    const int& operator[](int index) const {
        if (!in_bounds(index)) {
            throw std::out_of_range("Exception operator[](" + std::to_string(index) + ") Out Of Range");
        }
        return buf[index];
    }

    // Set every element of the array to 'val'
    void fill(int val) {
        std::fill_n(buf, len, val);
    }

private:
    int len;
    int* buf;

    bool in_bounds(int index) const {
        return index >= 0 && index < len;
    }
};

// Print array to 'out' in a single line.
inline std::ostream& operator<<(std::ostream& out, const Array& array) {
    for (int i = 0; i < array.length(); ++i) {
        out << array[i] << ' ';
    }
    return out;
}

// Read array from 'in', entries should be separated by whitespace.
inline std::istream& operator>>(std::istream& in, Array& array) {
    for (int i = 0; i < array.length(); ++i) {
        in >> array[i];
    }
    return in;
}

#endif // INT_ARRAY_HPP
