// similar to strcmp but for lists
int compare(Node* lhs, Node* rhs){
    // Traverse both lists
        while (head1 != nullptr && head2 != nullptr) {
            if (head1->data < head2->data) {
                return -1; // The first string is less than the second string
            }
            if (head1->data > head2->data) {
                return 1; // The first string is greater than the second string
            }
            // Move to the next nodes in the lists
            head1 = head1->next;
            head2 = head2->next;
        }

        // If both lists have reached the end, they are equal
        if (head1 == nullptr && head2 == nullptr) {
            return 0;
        }

        // If only the first list has reached the end, it is less than the second
        if (head1 == nullptr) {
            return -1;
        }

        // If only the second list has reached the end, the first is greater
        return 1;
}

// similar to strncmp but for lists
int compare(Node* lhs, Node* rhs, int n);