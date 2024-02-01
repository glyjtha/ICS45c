#include <gtest/gtest.h>

#include "string.hpp"

TEST(StringFunction, strlen) {
    EXPECT_EQ(String::strlen(""), 0);
    EXPECT_EQ(String::strlen("foo"), 3);
}

TEST(StringFunction, strcpy) {
    char result[10];
    EXPECT_EQ(String::strcpy(result, "foo"), result);
    EXPECT_STREQ(result, "foo");

    EXPECT_EQ(String::strcpy(result, "a"), result);
    EXPECT_STREQ(result, "a");

    EXPECT_EQ(String::strcpy(result, ""), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strncpy) {
    char result1[10];
    const char source[] = "Hello";

    // Test copying with enough space in the destination
    EXPECT_EQ(String::strncpy(result1, source, sizeof(result1)), result1);
    EXPECT_STREQ(result1, "Hello");


    // Test copying with the destination size exactly equal to the source length + null terminator
    char result3[6];
    EXPECT_EQ(String::strncpy(result3, source, sizeof(result3)), result3);
    EXPECT_STREQ(result3, "Hello");


    // Test copying with size limit less than the length of source string
    char result4[4];
    EXPECT_EQ(String::strncpy(result4, source, sizeof(result4)), result4);
    result4[sizeof(result4) - 1] = '\0'; // Manually null-terminate for safety
    EXPECT_STREQ(result4, "Hel");
}

TEST(StringFunction, strcat) {
    char result[20];
    result[0] = '\0';

    EXPECT_EQ(String::strcat(result, "Hello"), result);
    EXPECT_STREQ(result, "Hello");

    // Concatenate " World" to "Hello"
    EXPECT_EQ(String::strcat(result, " World"), result);
    EXPECT_STREQ(result, "Hello World");

    // Test concatenating an empty string
    EXPECT_EQ(String::strcat(result, ""), result);
    EXPECT_STREQ(result, "Hello World");

}


TEST(StringFunction, strncat) {
    char result[20]; // Initialize result with an empty string
    result[0] = '\0';

    // Test normal concatenation
    EXPECT_EQ(String::strncat(result, "Hello World", 11), result); // 11 includes the null terminator
    EXPECT_STREQ(result, "Hello World");

    // Edge Case: Source string longer than remaining buffer space
    char original[20]; // Create a copy of the original result
    strcpy(original, result);

    EXPECT_EQ(String::strncat(result, "!!!", 3), result); // Only space for 1 more char + null terminator
    EXPECT_STREQ(result, "Hello World!!!");

    // Restore the original result for the next test
    strcpy(result, original);

    // Edge Case: Concatenating an empty string
    EXPECT_EQ(String::strncat(result, "", 1), result); // Concatenating an empty string should change nothing
    EXPECT_STREQ(result, "Hello World");

    // Edge Case: Zero length concatenation
    EXPECT_EQ(String::strncat(result, "", 0), result); // Length 0 should change nothing
    EXPECT_STREQ(result, "Hello World");
}



TEST(StringFunction, strcmp) {
    const char source1[] = "Hello";
    const char source2[] = "Hello";
    const char source3[] = "World";
    const char source4[] = "";

    // Test equal strings
    EXPECT_EQ(String::strcmp(source1, source2), 0);

    // Test source1 < source3
    EXPECT_LT(String::strcmp(source1, source3), 0);

    // Test source3 > source1
    EXPECT_GT(String::strcmp(source3, source1), 0);

    //Test source 1 and empty
    EXPECT_GT(String::strcmp(source3, source4), 0);
    EXPECT_LT(String::strcmp(source4, source3), 0);
    
    //Test two empty
    EXPECT_EQ(String::strcmp(source4, source4), 0);


}


TEST(StringFunction, strncmp) {
    const char source1[] = "Hello";
    const char source2[] = "World";

    // Test equal for n characters
    EXPECT_EQ(String::strncmp(source1, source1, 5), 0);

    // Test source1 < source2 for first 3 characters
    EXPECT_LE(String::strncmp(source1, source2, 3), 0);

    // Comparing strings of different lengths
    // EXPECT_NE(String::strncmp(source1, "Hello World", 5), 0); // Compare only first 5 characters
}


TEST(StringFunction, reverse_cpy) {
    const char source[] = "Hello";
    char result[6];
    const char oneChar[] = "A";
    const char empty[] = "";

    // Test reversing a string
    String::reverse_cpy(result, source);
    EXPECT_STREQ(result, "olleH");

    // Edge Case: Reversing a single character
    String::reverse_cpy(result, oneChar);
    EXPECT_STREQ(result, "A");

    // Edge Case: Reversing an empty string
    String::reverse_cpy(result, empty);
    EXPECT_STREQ(result, "");
}


TEST(StringFunction, strchr) {
    const char source[] = "Hello World";
    const char empty[] = "";

    // Test finding a character in the string
    EXPECT_TRUE(String::strchr(source, 'W') != nullptr);

    // Edge Case: Character not in string
    EXPECT_TRUE(String::strchr(source, 'Z') == nullptr);

    // Edge Case: Searching in an empty string
    EXPECT_TRUE(String::strchr(empty, 'H') == nullptr);

    // Edge Case: Searching for null terminator
    // EXPECT_EQ(String::strchr(source, '\0'), source + strlen(source));


}

TEST(StringFunction, strstr) {
    const char source[] = "Hello World";
    const char empty[] = "";

    // Test finding a substring
    EXPECT_TRUE(String::strstr(source, "World") != nullptr);

    // Edge Case: Substring not in string
    EXPECT_TRUE(String::strstr(source, "Moon") == nullptr);

    // Edge Case: Searching in an empty string
    EXPECT_TRUE(String::strstr(empty, "Hello") == nullptr);

    // Edge Case: Searching for an empty substring
    EXPECT_EQ(String::strstr(source, empty), source);
}
