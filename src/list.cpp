#include <iostream>
#include "list.hpp"

list::Node* list::from_string(const char* s) {
    if (s == nullptr) {
        return nullptr;
    }

    if (s[0] == '\0') { 
        return nullptr;
    }

    Node* head = nullptr;
    Node* curr = nullptr;

    for (int i = 0; s[i] != '\0'; ++i) {
        Node* newNode = new Node{s[i], nullptr};
        
        if (head == nullptr) {
            head = newNode;
        } else {
            curr->next = newNode;
        }
        curr = newNode;
    }
    return head;
}


void list::free(Node* head){
    while (head != nullptr) {
        Node *temp = head->next;
        delete head;
        head = temp;
    }
}

void list::print(std::ostream& out, Node* head){
    Node* curr = head;
    while(curr != nullptr){
        out<< curr->data;
        curr = curr->next;
    }
}

list::Node* list::copy(Node* head){
    if (head==nullptr){
        return nullptr;
    }
    Node* result = new Node{head->data, nullptr};
    Node* curr = result;
    Node* temp = head->next;

    while (temp != nullptr) {
        curr->next = new Node{temp->data, nullptr}; 
        curr = curr->next; 
        temp = temp->next;
    }

    return result;
}

int list::compare(Node* lhs, Node* rhs) {
    while (lhs != nullptr && rhs != nullptr) {
        if (lhs->data < rhs->data) {
            return -1;
        }
        if (lhs->data > rhs->data) {
            return 1;
        }
        lhs = lhs->next;
        rhs = rhs->next;
    }

    if (lhs == nullptr && rhs == nullptr) {
        return 0;
    }

    if (lhs == nullptr) {
        return -1;
    }

    return 1;
}


int list::compare(Node* lhs, Node* rhs, int n) {
    int count = 0;
    while (lhs != nullptr && rhs != nullptr && count < n) {
        if (lhs->data != rhs->data) {
            return lhs->data - rhs->data;
        }
        lhs = lhs->next;
        rhs = rhs->next;
        count++;
    }

    if (count == n) {
        return 0;
    }

    if (lhs == nullptr && rhs == nullptr) {
        return 0;
    } else if (lhs == nullptr) {
        return -1;
    } else if (rhs == nullptr) {
        return 1;
    }

    return 0;
}

int list::length(Node* head) {
    if (head == nullptr) {
        return 0;
    }
    return 1 + length(head->next);
}

list::Node* list::reverse(Node* head) {
    Node* newHead = nullptr;

    while (head != nullptr) {
        Node* newNode = new Node{head->data, newHead};
        newHead = newNode;

        head = head->next;
    }
    return newHead;
}


list::Node* list::append(Node* lhs, Node* rhs){
    if (lhs == nullptr) {
        return copy(rhs);
    }

    if (rhs == nullptr) {
        return copy(lhs);
    }

    Node* result = copy(lhs);

    Node* curr = result;
    while (curr->next != nullptr) {
        curr = curr->next;
    }

    curr->next = copy(rhs);

    return result;
}

int list::index(Node* head, Node* node) {
    int count = 0;
    Node* curr = head;

    while (curr != nullptr) {
        if (curr == node) {
            return count;
        }
        curr = curr->next;
        ++count;
    }

    return -1;
}

list::Node* list::find_char(Node* head, char c) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == c) {
            return current; 
        }
        current = current->next;
    }
    return nullptr; // Character not found
}

list::Node* list::find_list(Node* haystack, Node* needle) {
    if (needle == nullptr) return haystack; // An empty needle is found in any haystack

    Node* currentHaystack = haystack;
    while (currentHaystack != nullptr) {
        Node* tempHaystack = currentHaystack;
        Node* tempNeedle = needle;

        while (tempHaystack != nullptr && tempNeedle != nullptr && tempHaystack->data == tempNeedle->data) {
            tempHaystack = tempHaystack->next;
            tempNeedle = tempNeedle->next;
        }

        if (tempNeedle == nullptr) {
            return currentHaystack; // Entire needle found in haystack
        }

        currentHaystack = currentHaystack->next;
    }

    return nullptr; // Needle not found in haystack
}

list::Node* list::nth(Node* head, int n) {
    Node* current = head;
    int count = 0;
    while (current != nullptr) {
        if (count == n) {
            return current; // n-th node found
        }
        current = current->next;
        ++count;
    }
    return nullptr; // n-th node not found (list is shorter than n)
}

list::Node* list::last(Node* head) {
    if (head == nullptr) {
        return nullptr; 
    }

    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current; 
}