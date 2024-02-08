#include "string.hpp"
#include <utility>
#include <iostream>


String::String(const char *s){
    if (s == nullptr){
        buf = new char[1];
        buf[0] = '\0';
    }
    else{
        buf = new char[strlen(s) + 1];
        strcpy(buf, s);

    }
}

String::String(const String &s){
    buf = new char[strlen(s.buf) + 1];
    strcpy(buf, s.buf);
}

String::String(String&& s)
    : buf(nullptr) 
{
    swap(s); 
}

String::String(int length) : buf(new char[length]) {
    std::fill_n(buf, length, '\0');
}

void String::swap(String& s){
    std::swap(buf, s.buf);
}

String& String::operator=(const String &s) {
    if (this != &s) { 
        String temp(s); 
        swap(temp);
    }
    return *this;
}

String& String::operator=(String&& s) {
    if (this != &s) {
        delete[] buf; 
        buf = s.buf; 
        s.buf = nullptr;
    }
    return *this;
}

char& String::operator[](int index) {
    if (in_bounds(index)){
        return buf[index];}
    else{
        std::cout << "ERROR: Index Out Of Bounds" << std::endl;
        return buf[0];
    }
}

const char& String::operator[](int index) const {
    if (in_bounds(index)){
        return buf[index];}
    else{
        std::cout << "ERROR: Index Out Of Bounds" << std::endl;
        return buf[0];
    }
}

int String::size() const{
    return strlen(buf);
}

String String::reverse() const {
    int len = size();
    String reversed(len + 1); 
    String::reverse_cpy(reversed.buf, buf);
    return reversed;
}



int String::indexOf(char c) const {
    for (int i = 0; buf[i] != '\0'; ++i) {
        if (buf[i] == c) {
            return i; 
        }
    }
    return -1; 
}

int String::indexOf(const String& s) const {
    int len = strlen(buf);
    int sublen = s.size();

    if (sublen == 0) {
        return 0;
    }

    for (int i = 0; i <= len - sublen; ++i) {
        int j;
        for (j = 0; j < sublen; ++j) {
            if (buf[i + j] != s.buf[j]) {
                break; 
            }
        }
        if (j == sublen) {
            return i; 
        }
    }
    return -1; 
}



bool String::operator==(const String &s) const {
    bool value = strcmp(buf, s.buf) == 0;
    return value;
}

bool String::operator!=(const String &s) const {
    return !(*this == s);
}

bool String::operator>(const String &s) const {
    bool value = strcmp(buf, s.buf) > 0;
    return value;
}

bool String::operator<(const String &s) const {
    return !(*this == s) && !(*this > s);
}

bool String::operator<=(const String &s) const {
    return !(*this > s);
}

bool String::operator>=(const String &s) const {
    return *this == s || *this > s;
}


String String::operator+(const String &s) const {
    int thisLen = strlen(buf);
    int otherLen = strlen(s.buf);
    int totalLen = thisLen + otherLen;

    String result(totalLen + 1); // Use private constructor to allocate buffer

    strcpy(result.buf, buf);
    strcat(result.buf, s.buf);

    return result;
}

String& String::operator+=(const String &s) {
    int thisLen = strlen(buf);
    int otherLen = strlen(s.buf);
    int totalLen = thisLen + otherLen;

    String temp(totalLen + 1); 

    strcpy(temp.buf, buf);
    strcat(temp.buf, s.buf);

    delete[] buf;  // Free old buffer
    buf = temp.buf; // Reuse the buffer from temp
    temp.buf = nullptr; // Prevent deletion in temp's destructor

    return *this;
}



void String::print(std::ostream &out) const{
    out << buf;
}

void String::read(std::istream &in) {
    const int bufferSize = 100;  // Initial buffer size
    char temp[bufferSize];       // Temporary buffer to store input

    if (in >> temp) {            // Read next word from the input stream
        delete[] buf;            // Delete old buffer
        int length = strlen(temp);
        buf = new char[length + 1];  // Allocate memory for new word
        strcpy(buf, temp);           // Copy the word into buf
    }
}
String::~String() {
    delete[] buf;
}

bool String::in_bounds(int i) const {
    return i >= 0 && i < strlen(buf);
}

int String::strlen(const char *s){
    int length = 0;
    while(s[length] != '\0'){
        length++;
    }
    return length;
}

char* String::strcpy(char* dest, const char* src) {
     int i = 0;
      for ( i = 0; src[i] != '\0'; ++i)  
      {
	    dest[i] = src[i];
      }
      dest[i]  = '\0';
      return dest;
}

char* String::strdup(const char *src){
    int length = strlen(src);
    char* new_str = new char[length + 1]; // +1 for null terminator
    strcpy(new_str, src);
    return new_str;
}

char *String::strncpy(char *dest, const char *src, int n) {
    int i;
    for(i=0; i<n && src[i] != '\0'; ++i){
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}

char *String::strcat(char *dest, const char *src) {
    int dest_len = strlen(dest); 
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        ++i;
    }
    dest[dest_len + i] = '\0'; // Null-terminate the concatenated string
    return dest;
}

char *String::strncat(char *dest, const char *src, int n) {
    int dest_len = strlen(dest);
    int i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len + i] = '\0';
    return dest;
}

int String::strcmp(const char *left, const char *right){
    int i = 0;
    while (left[i] == right[i]) {
        if (left[i] == '\0') {
            return 0; // Strings are equal
        }
        ++i;
    }
    return (unsigned char)left[i] - (unsigned char)right[i];
}

int String::strncmp(const char *left, const char *right, int n){
    for (int i = 0; i < n; ++i) {
        if (left[i] == '\0' || right[i] == '\0') {
            return (unsigned char)left[i] - (unsigned char)right[i];
        }

        // If characters differ, return the difference
        if (left[i] != right[i]) {
            return (unsigned char)left[i] - (unsigned char)right[i];
        }
    }
    return 0;
}


void String::reverse_cpy(char *dest, const char *src) {
    int len = strlen(src);
    for (int i = 0; i < len; ++i) {
        dest[len - 1 - i] = src[i];
    }
    dest[len] = '\0';
}

const char *String::strchr(const char *src, char c) {
    while (true) {
        if (*src == c) {
            return src; 
        }
        if (*src == '\0') {
            break; 
        }
        ++src;
    }
    return nullptr; // Character not found
}

const char *String::strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') {
        return haystack; // Empty needle should return the full haystack
    }
    int len = strlen(needle);

    for (const char *p = haystack; *p != '\0'; ++p) {
        if (strlen(p) < len) {
            return nullptr; 
        }
        if (*p == needle[0]) {
            if (strncmp(p, needle, len) == 0) {
                return p;
            }
        }
    }
    return nullptr;
}

std::ostream &operator<<(std::ostream &out, const String &s) {
    s.print(out);
    return out;
}

std::istream &operator>>(std::istream &in, String &s) {
    s.read(in);
    return in;
}