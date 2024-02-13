#include <iostream>
using namespace std;

Node* from_string(const char* s) {
    if (s == nullptr) {
        return nullptr;
    }

    Node* head = new Node{s[0], nullptr};
    Node* curr = head;

    for (int i = 1; s[i] != '\0'; ++i) {
        curr->next = new Node{s[i], nullptr};
        curr = curr->next;
    }
    return head;
}

void free(Node* head){
    while (head != nullptr) {
        Node *temp = head->next;
        delete head;
        head = temp;
    }
}

void print(std::ostream& out, Node* head){
    Node* curr = head;
    while(curr != nullptr){
        out<< curr->data;
        curr = curr->next;
    }
}

Node* copy(Node* head){
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

int list::compare(Node* lhs, Node* rhs){
        while (head1 != nullptr && head2 != nullptr) {
            if (head1->data < head2->data) {
                return -1;
            }
            if (head1->data > head2->data) {
                return 1;
            }
            head1 = head1->next;
            head2 = head2->next;
        }

        if (head1 == nullptr && head2 == nullptr) {
            return 0;
        }

        if (head1 == nullptr) {
            return -1;
        }

        return 1;
}

int list::compare(Node* lhs, Node* rhs, int n){
    int count = 0;
    while(lhs != nullptr && rhs != nullptr && count < n){
        if (lhs->data != rhs->data) {
            return lhs->data - rhs->data;
        }
    lhs = lhs->next;
    rhs = rhs->next;
    count++;
    }

    if (count == n || (lhs == nullptr && rhs == nullptr)) {
        return 0;
    }

    if (lhs == nullptr){
        return -1;
    }

    if(rhs == nullptr){
        return 1;
    }

    return 0;
}

int length(Node* head) {
    if (head == nullptr) {
        return 0;
    }
    return 1 + length(head->next);
}

Node* reverse(Node* head) {
    Node* curr = head;
    Node* prev = nullptr;
    Node* next = nullptr;

    while (curr != nullptr) {
        // Store next
        next = curr->next;

        // Reverse current node's pointer
        curr->next = prev;

        // Move pointers one position ahead
        prev = curr;
        curr = next;
    }

    return prev;
}

Node* append(Node* lhs, Node* rhs){
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

int index(Node* head, Node* node) {
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

Node* find_char(Node* head, char c) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == c) {
            return current; 
        }
        current = current->next;
    }
    return nullptr; // Character not found
}

Node* find_list(Node* haystack, Node* needle) {
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

Node* nth(Node* head, int n) {
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

Node* last(Node* head) {
    if (head == nullptr) {
        return nullptr; 
    }

    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current; 
}