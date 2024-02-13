#include <iostream>
#include <compare>


#include "alloc.hpp"
#include "string.hpp"

using namespace std;

bool String::operator==(const String& other) const {
    if (this == &other) {
        return true;
    }

    list::Node* current1 = this->head;
    list::Node* current2 = other.head;

    while (current1 != nullptr && current2 != nullptr) {
        if (current1->data != current2->data) {
            return false; 
        }
        current1 = current1->next;
        current2 = current2->next;
    }

    return current1 == nullptr && current2 == nullptr;
    }

bool String::operator!=(const String& other) const {//negating operator==
    return !(*this == other);
}

std::strong_ordering String::operator<=>(const String &other) const {
    int cmp = list::compare(head, other.head);
    if (cmp < 0) {
        return std::strong_ordering::less;
    }
    if (cmp > 0) { 
        return std::strong_ordering::greater;
    }
    return std::strong_ordering::equal;
}
