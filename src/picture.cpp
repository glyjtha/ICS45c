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
Picture::Picture(Picture&& other)
    : head(other.head), tail(other.tail) {
    other.head = nullptr;
    other.tail = nullptr;
}

void Picture::swap(Picture& other){
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

Picture& Picture::operator=(const Picture& other){
    if (this != &other) { 
        Picture temp(other); 
        swap(temp);
    }
    return *this;
}

Picture& Picture::operator=(Picture&& other) noexcept {
    if (this != &other) {
        // Release any existing resources
        ListNode* current = head;
        while (current != nullptr) {
            ListNode* next = current->next;
            delete current->shape;  // Assuming shape is dynamically allocated
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    

        // Transfer ownership of resources
        head = other.head;
        tail = other.tail;

        // Set 'other' to a safe empty state
        other.head = nullptr;
        other.tail = nullptr;
    }
    return *this;
}


void Picture::add(const Shape& shape){
     ListNode* newNode = new ListNode{shape.clone(), nullptr};

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void Picture::print_all(std::ostream& out) const {
    ListNode* current = head;
    while (current != nullptr) {
        current->shape->print(out);
        current = current->next;
    }
}

void Picture::draw_all(std::ostream& out) const{
    ListNode* current = head;
    while (current != nullptr){
        current->shape ->draw(out);
        current = current->next;
    }
}

double Picture::total_area() const {
    double area = 0.0;
    ListNode* current = head;
    while (current != nullptr) {
        area += current->shape->area(); 
        current = current->next;
    }
    return area;
}

Picture::~Picture() {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* next = current->next;
        delete current->shape; // Deallocate the shape
        delete current; // Deallocate the node
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}