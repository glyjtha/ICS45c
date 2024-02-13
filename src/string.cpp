#include <iostream>
#include <compare>


#include "alloc.hpp"
#include "string.hpp"

using namespace std;

// String::String(const char *s) {
//     if (s) {
//         head = nullptr;
//         list::Node* tail = nullptr;
//         while (*s) {
//             list::Node* newNode = new list::Node{*s, nullptr};
//             if (!head) {
//                 head = newNode;
//             } else {
//                 tail->next = newNode;
//             }
//             tail = newNode;
//             ++s;
//         }
//     } else {
//         head = nullptr;
//     }
// }

// String::String(const String &s) : head(nullptr) {
//     if (s.head) {
//         head = new list::Node{s.head->data, nullptr};
//         list::Node* srcNode = s.head->next;
//         list::Node* destNode = head;
//         while (srcNode) {
//             destNode->next = new list::Node{srcNode->data, nullptr};
//             destNode = destNode->next;
//             srcNode = srcNode->next;
//         }
//     }
//     else{
//         head = nullptr;
//     }
// }


bool String::operator==(const String& other) const {
    if (this == &other) {
        return true; // Self-comparison
    }

    list::Node* current1 = this->head;
    list::Node* current2 = other.head;

    while (current1 != nullptr && current2 != nullptr) {
        if (current1->data != current2->data) {
            return false; // Characters differ
        }
        current1 = current1->next;
        current2 = current2->next;
    }

    // Check if both lists reached the end (same length)
    return current1 == nullptr && current2 == nullptr;
}


std::strong_ordering String::operator<=>(const String &other) const {
    return list::compare(head, other.head) <=> 0;
}
