#include <iostream>
#include <compare>


#include "alloc.hpp"
#include "string.hpp"

using namespace std;

String::String(const char* s) : head(list::from_string(s)) {}

String::String(const String& s) : head(list::copy(s.head)) {}

String::String(String&& s) : head(s.head) {
    s.head = nullptr;
}

void String::swap(String &s) {
    std::swap(head, s.head);
}

String& String::operator=(const String& s) {
    if (this != &s) {
        String temp(s);
        swap(temp);
    }
    return *this;
}

String& String::operator=(String&& s) {
    swap(s);
    return *this;
}

bool String::in_bounds(int index) const {
    return index >= 0 && index < list::length(head);
}


char String::operator[](int index) const {
    list::Node* node = list::nth(head, index);
    return node ? node->data : '\0';
}

int String::size() const {
    return list::length(head);
}

String String::reverse() const {
    return String(list::reverse(head));
}

int String::indexOf(char c) const {
    list::Node* node = list::find_char(head, c);
    return list::index(head, node);
}


int String::indexOf(const String& s) const {
    list::Node* startNode = list::find_list(head, s.head);
    return list::index(head, startNode);
}


bool String::operator==(const String& s) const {
    return (*this <=> s) == std::strong_ordering::equal;
}

std::strong_ordering String::operator<=>(const String &other) const {
    return list::compare(head, other.head) <=> 0;
}

String String::operator+(const String& s) const {
    return String(list::append(head, s.head));
}

String& String::operator+=(const String& s) {
    list::Node* newHead = list::append(head, s.head);
    list::free(head);
    head = newHead;
    return *this;
}

void String::print(std::ostream& out) const {
    list::print(out, head);
}

void String::read(std::istream& in) {
    char buffer[1024];
    in >> buffer;
    list::free(head);
    head = list::from_string(buffer);
}

String::~String() {
    list::free(head);
}

String::String(list::Node* headNode) : head(headNode) {}

std::ostream &operator<<(std::ostream &out, const String &s){
    s.print(out);
    return out;
}
std::istream &operator>>(std::istream &in, String &s){
    s.read(in);
    return in;
}