#include <gtest/gtest.h>

#include "list.hpp"

using namespace std;
using list::Node;

TEST(ListTests, FromStringBasic) {
    Node* const foo_list_head = list::from_string("foo");

    // Ensure the list head is not null before proceeding
    ASSERT_NE(foo_list_head, nullptr);

    Node* foo_list = foo_list_head;
    EXPECT_EQ(foo_list->data, 'f');
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_EQ(foo_list->next, nullptr);


    Node* empty_list_head = list::from_string("");
    EXPECT_EQ(empty_list_head, nullptr);
    
    list::free(foo_list_head);
}

TEST(ListTests, Length) {
    Node* const head = list::from_string("foo");
    EXPECT_EQ(list::length(head), 3);
    list::free(head);

    Node* const empty = list::from_string("");
    EXPECT_EQ(list::length(empty), 0);

}

// Add remaining tests below. All tests should follow
// the format of `TEST(ListTests, <TestName>){}`.

TEST(ListTests, Free) {
    Node* head = list::from_string("foo");
    list::free(head);

    Node* empty = list::from_string("");
    list::free(empty);

    Node* nullhead = nullptr;
    list::free(nullhead);
}

TEST(ListTests, Print) {
    //list
    Node* head = list::from_string("foo");
    testing::internal::CaptureStdout();
    list::print(std::cout, head);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "foo");
    list::free(head);

    //empty
    Node* emptyhead = list::from_string("");
    testing::internal::CaptureStdout();
    list::print(std::cout, emptyhead);
    std::string output1 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output1, "");

    //nullptr
    Node* nullhead = nullptr;
    testing::internal::CaptureStdout();
    list::print(std::cout, nullhead);
    std::string output2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output2, "");
}

TEST(ListTests, Copy) {
    Node* foo_list = list::from_string("foo");
    Node* copiedList = list::copy(foo_list);

    Node* foolCurr = foo_list;
    Node* copiedCurr = copiedList;
    while (foolCurr != nullptr && copiedCurr != nullptr) {
        EXPECT_EQ(copiedCurr->data, foolCurr->data);
        foolCurr = foolCurr->next;
        copiedCurr = copiedCurr->next;
    }

    EXPECT_EQ(foolCurr, nullptr);
    EXPECT_EQ(copiedCurr, nullptr);

    list::free(foo_list);      // Corrected: Free the original list, not the iterator
    list::free(copiedList);

    Node* empty_list = list::from_string("");
    Node* emptycopiedList = list::copy(empty_list);
    EXPECT_EQ(emptycopiedList, nullptr);  // Corrected: Check for nullptr

    Node* null_list = nullptr;
    Node* emptycopiedList1 = list::copy(null_list);
    EXPECT_EQ(emptycopiedList1, nullptr); // Corrected: Check for nullptr

    list::free(empty_list);    // Free the empty_list
    list::free(emptycopiedList);
    list::free(emptycopiedList1);
}


TEST(ListTests, Compare) {
    //equal
    Node* list1 = list::from_string("foo");
    Node* list2 = list::from_string("foo");
    EXPECT_EQ(list::compare(list1, list2), 0);
    list::free(list1);
    list::free(list2);

    //lhs less than rhs
    Node* list3 = list::from_string("boo");
    Node* list4 = list::from_string("foo");
    EXPECT_EQ(list::compare(list3, list4), -4);
    list::free(list3);
    list::free(list4);

    //rhs less than lhs
    Node* list5 = list::from_string("foo");
    Node* list6 = list::from_string("boo");
    EXPECT_EQ(list::compare(list5, list6), 4);
    list::free(list5);
    list::free(list6);

    //lhs shorter than rhs
    Node* list7 = list::from_string("bo");
    Node* list8 = list::from_string("foo");
    EXPECT_EQ(list::compare(list7, list8), -4);
    list::free(list7);
    list::free(list8);

    //rhs shorter than lhs
    Node* list9 = list::from_string("foo");
    Node* list10 = list::from_string("bo");
    EXPECT_EQ(list::compare(list9, list10), 4);
    list::free(list9);
    list::free(list10);

    //nullptr
    Node* list11 = nullptr;
    Node* list12 = nullptr;
    EXPECT_EQ(list::compare(list11, list12), 0);

    //empty
    Node* list13 = list::from_string("");
    Node* list14 = list::from_string("");
    EXPECT_EQ(list::compare(list13, list14), 0);

}

TEST(ListTests, CompareN) {
    // Equal up to n characters
    Node* list1 = list::from_string("foobar");
    Node* list2 = list::from_string("foobaz");
    EXPECT_EQ(list::compare(list1, list2, 3), 0);
    list::free(list1);
    list::free(list2);

    // Lhs less than rhs within n characters
    Node* list3 = list::from_string("boo");
    Node* list4 = list::from_string("foo");
    EXPECT_EQ(list::compare(list3, list4, 2), -4);
    list::free(list3);
    list::free(list4);

    // Rhs less than lhs within n characters
    Node* list5 = list::from_string("foo");
    Node* list6 = list::from_string("boo");
    EXPECT_EQ(list::compare(list5, list6, 2), 4);
    list::free(list5);
    list::free(list6);

    // Lhs shorter than n
    Node* list7 = list::from_string("bo");
    Node* list8 = list::from_string("foo");
    EXPECT_EQ(list::compare(list7, list8, 3), -4);
    list::free(list7);
    list::free(list8);

    // Rhs shorter than n
    Node* list9 = list::from_string("foo");
    Node* list10 = list::from_string("bo");
    EXPECT_EQ(list::compare(list9, list10, 3), 4);
    list::free(list9);
    list::free(list10);

    // Comparing nullptrs
    Node* list11 = nullptr;
    Node* list12 = nullptr;
    EXPECT_EQ(list::compare(list11, list12, 3), 0);

    // Comparing empty lists
    Node* list13 = list::from_string("");
    Node* list14 = list::from_string("");
    EXPECT_EQ(list::compare(list13, list14, 3), 0);

    Node* list15 = list::from_string("abcd");
    Node* list16 = list::from_string("abcf");
    EXPECT_NE(list::compare(list15, list16, 4), 0);
    list::free(list15);
    list::free(list16);

    Node* list17 = list::from_string("xyz");
    Node* list18 = list::from_string("abc");
    EXPECT_EQ(list::compare(list17, list18, 0), 0);
    list::free(list17);
    list::free(list18);

    Node* list19 = nullptr;
    Node* list20 = list::from_string("abc");
    EXPECT_EQ(list::compare(list19, list20, 3), -1);
    EXPECT_EQ(list::compare(list20, list19, 3), 1);
    list::free(list20);
}


TEST(ListTests, Reverse) {
    //nullptr
    Node* nullList = nullptr;
    Node* reversedList = list::reverse(nullList);
    EXPECT_EQ(reversedList, nullptr);

    //empty
    Node* emptyList = list::from_string("");;
    Node* reversedList1 = list::reverse(emptyList);
    EXPECT_EQ(reversedList1, nullptr);

    //single
    Node* singleElementList = list::from_string("a");
    Node* reversedList2 = list::reverse(singleElementList);
    ASSERT_NE(reversedList2, nullptr);
    EXPECT_EQ(reversedList2->data, 'a');
    EXPECT_EQ(reversedList2->next, nullptr);
    list::free(singleElementList);
    list::free(reversedList2);

    //word
    Node* multiElementList = list::from_string("abc");
    Node* reversedList3 = list::reverse(multiElementList);
    std::string reversedStr;
    Node* curr = reversedList3;
    while (curr != nullptr) {
        reversedStr.push_back(curr->data);
        curr = curr->next;
    }
    EXPECT_EQ(reversedStr, "cba");
    list::free(multiElementList);
    list::free(reversedList3);


}

std::string list_to_string(Node* head) {
    std::string result;
    while (head) {
        result.push_back(head->data);
        head = head->next;
    }
    return result;
}

TEST(ListTests, Append) {
    // Append two non-empty lists
    Node* list1 = list::from_string("abc");
    Node* list2 = list::from_string("def");
    Node* appendedList1 = list::append(list1, list2);
    std::string appendedStr1 = list_to_string(appendedList1); // Helper function to convert list to string
    EXPECT_EQ(appendedStr1, "abcdef");
    list::free(list1);
    list::free(list2);
    list::free(appendedList1);

    // Append non-empty list to empty list
    Node* list3 = list::from_string("");
    Node* list4 = list::from_string("xyz");
    Node* appendedList2 = list::append(list3, list4);
    std::string appendedStr2 = list_to_string(appendedList2);
    EXPECT_EQ(appendedStr2, "xyz");
    list::free(list3);
    list::free(list4);
    list::free(appendedList2);

    // Append empty list to non-empty list
    Node* list5 = list::from_string("abc");
    Node* list6 = list::from_string("");
    Node* appendedList3 = list::append(list5, list6);
    std::string appendedStr3 = list_to_string(appendedList3);
    EXPECT_EQ(appendedStr3, "abc");
    list::free(list5);
    list::free(list6);
    list::free(appendedList3);

    // Append two empty lists
    Node* list7 = list::from_string("");
    Node* list8 = list::from_string("");
    Node* appendedList4 = list::append(list7, list8);
    std::string appendedStr4 = list_to_string(appendedList4);
    EXPECT_EQ(appendedStr4, "");
    list::free(list7);
    list::free(list8);
    list::free(appendedList4);
}


TEST(ListTests, Index) {
    Node* list = list::from_string("abcde");

    // Test finding each node in the list
    Node* curr = list;
    int expectedIndex = 0;
    while (curr != nullptr) {
        EXPECT_EQ(list::index(list, curr), expectedIndex);
        curr = curr->next;
        ++expectedIndex;
    }

    // Test empty list
    Node* emptyList = "";
    Node* someNode = new Node{'y', nullptr};
    EXPECT_EQ(list::index(emptyList, someNode), -1);
    delete someNode;

    list::free(list);
}

TEST(ListTests, FindChar) {
    Node* list = list::from_string("hello");

    // Test finding each character in the list
    std::string testStr = "hello";
    for (char c : testStr) {
        Node* foundNode = list::find_char(list, c);
        ASSERT_NE(foundNode, nullptr);
        EXPECT_EQ(foundNode->data, c);
    }

    // Test character not in the list
    EXPECT_EQ(list::find_char(list, 'x'), nullptr);

    // Test empty list
    Node* emptyList = nullptr;
    EXPECT_EQ(list::find_char(emptyList, 'h'), nullptr);

    // Free the list
    list::free(list);
}

TEST(ListTests, FindList) {
    // Create a haystack list for testing
    Node* haystack = list::from_string("abcde");

    // Test finding a sublist in the haystack
    Node* sublist1 = list::from_string("cd");
    Node* found1 = list::find_list(haystack, sublist1);
    ASSERT_NE(found1, nullptr);
    EXPECT_EQ(found1->data, 'c');
    list::free(sublist1);

    // Test not finding a non-existent sublist
    Node* sublist2 = list::from_string("xyz");
    Node* found2 = list::find_list(haystack, sublist2);
    EXPECT_EQ(found2, nullptr);
    list::free(sublist2);

    // Test with an empty sublist (needle), should return haystack
    Node* emptySublist = nullptr;
    Node* found3 = list::find_list(haystack, emptySublist);
    EXPECT_EQ(found3, haystack);

    // Test searching in an empty haystack
    Node* emptyHaystack = nullptr;
    Node* sublist3 = list::from_string("a");
    Node* found4 = list::find_list(emptyHaystack, sublist3);
    EXPECT_EQ(found4, nullptr);
    list::free(sublist3);

    // Free the haystack list
    list::free(haystack);
}

TEST(ListTests, NthNode) {
    Node* list = list::from_string("abcde");

    // Test position beyond list length
    Node* beyondNode = list::nth(list, 10);
    EXPECT_EQ(beyondNode, nullptr);

    // Test negative index, should return nullptr
    Node* negativeIndexNode = list::nth(list, -1);
    EXPECT_EQ(negativeIndexNode, nullptr);

    // Test empty list
    Node* emptyList = "";
    Node* nthInEmpty = list::nth(emptyList, 2);
    EXPECT_EQ(nthInEmpty, nullptr);

    // Free the list
    list::free(list);
}

TEST(ListTests, LastNode) {
    // Test last node in non-empty list
    Node* nonEmptyList = list::from_string("abc");
    Node* lastNode = list::last(nonEmptyList);
    ASSERT_NE(lastNode, nullptr);
    EXPECT_EQ(lastNode->data, 'c');
    list::free(nonEmptyList);

    // Test last node in empty list
    Node* emptyList = "";
    Node* lastNodeInEmpty = list::last(emptyList);
    EXPECT_EQ(lastNodeInEmpty, nullptr);

    // Test last node in single node list
    Node* singleNodeList = list::from_string("a");
    Node* lastNodeInSingle = list::last(singleNodeList);
    ASSERT_NE(lastNodeInSingle, nullptr);
    EXPECT_EQ(lastNodeInSingle->data, 'a');
    list::free(singleNodeList);
}

