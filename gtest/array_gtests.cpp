#include <gtest/gtest.h>

#include <string>

#include "array.hpp"

using namespace std;

TEST(ArrayTests, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.length(), 0);
}

TEST(ArrayTests, ConstructorWithLength) {
    Array<int> arr(5);
    EXPECT_EQ(arr.length(), 5);
}

TEST(ArrayTests, CopyConstructor) {
    Array<int> arr1(5);
    arr1[0] = 10;
    Array<int> arr2(arr1);
    EXPECT_EQ(arr2.length(), 5);
    EXPECT_EQ(arr2[0], 10);
}

TEST(ArrayTests, MoveConstructor) {
    Array<int> arr1(5);
    arr1[0] = 10;
    Array<int> arr2(std::move(arr1));
    EXPECT_EQ(arr2.length(), 5);
    EXPECT_EQ(arr2[0], 10);
    EXPECT_EQ(arr1.length(), 0); 
}

TEST(ArrayTests, CopyAssignment) {
    Array<int> arr1(5);
    arr1[0] = 10;
    Array<int> arr2;
    arr2 = arr1;
    EXPECT_EQ(arr2.length(), 5);
    EXPECT_EQ(arr2[0], 10);
}

TEST(ArrayTests, MoveAssignment) {
    Array<int> arr1(5);
    arr1[0] = 10;
    Array<int> arr2;
    arr2 = std::move(arr1);
    EXPECT_EQ(arr2.length(), 5);
    EXPECT_EQ(arr2[0], 10);
    EXPECT_EQ(arr1.length(), 0); 
}

TEST(ArrayTests, IndexOperator) {
    Array<int> arr(5);
    arr[0] = 10;
    EXPECT_EQ(arr[0], 10);
}

TEST(ArrayTests, OutOfBoundsIndexAccess) {
    Array<int> arr(5);
    EXPECT_THROW(arr[10], std::out_of_range);
}


TEST(ArrayTests, Length) {
    Array<int> arr{3};
    EXPECT_EQ(arr.length(), 3);

    Array<string> arr2{10};
    EXPECT_EQ(arr2.length(), 10);

    EXPECT_EQ(Array<double>{}.length(), 0);
}

TEST(ArrayTests, FillWithFunction) {
    // Test with int
    Array<int> intArray(5);
    intArray.fill_with_fn([](int index) { return index * 2; }); // Fill with even numbers

    for (int i = 0; i < intArray.length(); ++i) {
        EXPECT_EQ(intArray[i], i * 2);
    }

    // Test with string
    Array<std::string> stringArray(5);
    stringArray.fill_with_fn([](int index) { return std::string("str") + std::to_string(index); });

    for (int i = 0; i < stringArray.length(); ++i) {
        EXPECT_EQ(stringArray[i], "str" + std::to_string(i));
    }

    // Test with double
    Array<double> doubleArray(5);
    doubleArray.fill_with_fn([](int index) { return index * 1.5; }); // Fill with multiples of 1.5

    for (int i = 0; i < doubleArray.length(); ++i) {
        EXPECT_DOUBLE_EQ(doubleArray[i], i * 1.5);
    }
}
