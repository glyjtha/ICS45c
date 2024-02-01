#include <iostream>
#include "string.hpp"
using namespace std;

// Implement the constructor from a C-string, defaults to empty string
String::String(const char *s) {
    // Call the static helper method strncpy
    strncpy(buf, s, MAXLEN - 1);
    buf[MAXLEN - 1] = '\0'; // Ensure the string is null-terminated
}

String::String(const String &s) {
    strncpy(buf, s.buf, MAXLEN - 1);
    buf[MAXLEN - 1] = '\0'; // Ensure the string is null-terminated
}



String& String::operator=(const String &s) {
    if (this != &s) {
        strncpy(buf, s.buf, MAXLEN - 1);
        buf[MAXLEN - 1] = '\0';
    }
    return *this;
}

char &String::operator[](int index) {
    if (index < 0 || index >= strlen(buf)) {
        // Returning first character as a fallback for out-of-bounds index
        return buf[0];
    } else {
        return buf[index]; // Return character at the given index
    }
}


int String::size() {
    return strlen(buf);
}


String String::reverse(){
    char temp[MAXLEN];
    reverse_cpy(temp, buf); 
    return String(temp);
}

int String::indexOf(char c){
    for (int i=0; buf[i] != '\0'; ++i){
        if (buf[i] == c){
            return i;
        }
    }
    return -1;
}

int String::indexOf(const String &s){ 
    if (strlen(s.buf) == 0) {
        return 0; // If s is an empty string, return 0
    }

    for (int i = 0; buf[i] != '\0'; ++i) {
        bool match = true;
        for (int j = 0; j < strlen(s.buf) && buf[i + j] != '\0'; ++j) { // Also check for the end of *this
            if (buf[i + j] != s.buf[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return i; // Found the substring
        }
    }
    return -1; // Substring not found
}


bool String::operator==(const String &s) const {
    // check if the lengths of the two strings are the same
    if (strlen(buf) != strlen(s.buf)) {
        return false; // Different lengths, so they cannot be equal
    }

    // Compare characters of both strings
    for (int i = 0; buf[i] != '\0'; ++i) {
        if (buf[i] != s.buf[i]) {
            return false; // Found a mismatching character
        }
    }

    return true; // All characters matched
}

bool String::operator!=(const String &s) const {
    return !(*this == s); // Use the already defined operator==
}

bool String::operator>(const String &s) const {
    int i = 0;
    while (buf[i] != '\0' && s.buf[i] != '\0') {
        if (buf[i] > s.buf[i]) {
            return true;  // Current string character is greater
        } else if (buf[i] < s.buf[i]) {
            return false; // Current string character is less
        }
        i++;
    }

    // If one string is a prefix of the other, the longer string is greater
    return buf[i] != '\0';

}

bool String::operator<(const String &s) const {
    int i = 0;
    while (buf[i] != '\0' && s.buf[i] != '\0') {
        if (buf[i] < s.buf[i]) {
            return true;  // Current string character is less
        } else if (buf[i] > s.buf[i]) {
            return false; // Current string character is greater
        }
        i++;
    }
    return buf[i] == '\0' && s.buf[i] != '\0'; // Return true if current string is shorter
}


bool String::operator>=(const String &s) const {
    return !(*this < s); // Use the already defined operator<
}


bool String::operator<=(const String &s) const {
    return !(*this > s); // Use the already defined operator>
}

String String::operator+(const String &s) {
    String result;
    strncpy(result.buf, buf, MAXLEN - 1);
    int length = strlen(result.buf);

    if (length < MAXLEN - 1) {
        strncat(result.buf, s.buf, MAXLEN - 1 - length);
    } else {
        std::cerr << "ERROR: String Capacity Exceeded" << std::endl;
    }

    result.buf[MAXLEN - 1] = '\0';
    return result;
}


String &String::operator+=(const String &s) {
    int thisLength = strlen(buf);
    int appendLength = strlen(s.buf);

    if (thisLength + appendLength >= MAXLEN) {
        std::cerr << "ERROR: String Capacity Exceeded" << std::endl;
        strncat(buf, s.buf, MAXLEN - 1 - thisLength);
    } else {
        strcat(buf, s.buf);
    }

    buf[MAXLEN - 1] = '\0';
    return *this;
}


void String::print(std::ostream &out) const{
    out << buf;
}

void String::read(std::istream &in){
    in >> buf;
    if (strlen(buf) >= MAXLEN){
        std::cout << "ERROR: String Capacity Exceeded"<< std::endl;
        }
}

String::~String(){

}

// Static helper function to copy a C-string with length protection

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

char *String::strncpy(char *dest, const char *src, int n) {
    int i = 0;
    // Copy characters from src to dest until null byte or limit is reached
    for (; i < n && src[i] != '\0'; ++i) {
        dest[i] = src[i];
    }
    // If less than n characters were copied, pad the rest with '\0'
    for (; i < n; ++i) {
        dest[i] = '\0';
    }
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
    for(int i=0; i < n; ++i){
        if(left[i] == '\0'|| left[i] == right[i]){
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
    while (*src != '\0') {
        if (*src == c) {
            return src; // src is 'const char*', so this is okay
        }
        ++src;
    }
    return nullptr;
}

const char *String::strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') {
        return haystack; // Empty needle should return the full haystack
    }

    int len = strlen(needle);

    for (const char *p = haystack; *p != '\0'; ++p) {
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
