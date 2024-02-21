#include "picture.hpp"
#include <iostream>
#include <utility>
#include <algorithm>

Picture::Picture(): head(nullptr), tail(nullptr){}

//copy constructor
Picture::Picture(const Picture& other): head(nullptr), tail(nullptr){
    ListNode* current = other.head;
    while (current != nullptr) {
        add(*(current->shape)); // Assuming 'add' method clones the shape and adds it to the list
        current = current->next;
    }
}

//move constructor
Picture::Picture(Picture&& other): head(nullptr), tail(nullptr){
    other.head = nullptr;
    other.tail = nullptr;
}

void Picture::swap(Picture& other){
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

Picture& Picture::operator=(const Picture& other){
}
