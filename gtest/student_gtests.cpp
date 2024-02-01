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

    EXPECT_EQ(String::strncpy(result1, source, sizeof(result1)), result1);
    EXPECT_STREQ(result1, "Hello");

    char result3[6];
    EXPECT_EQ(String::strncpy(result3, source, sizeof(result3)), result3);
    EXPECT_STREQ(result3, "Hello");


    char result5[8];
    EXPECT_EQ(String::strncpy(result5, source, sizeof(result5)), result5);
    EXPECT_STREQ(result5, "Hello");
    EXPECT_EQ(result5[6], '\0'); // Check padding

    char result6[10] = "Test";
    EXPECT_EQ(String::strncpy(result6, source, 0), result6);
    EXPECT_STREQ(result6, ""); // No change expected

    char result7[10];
    EXPECT_EQ(String::strncpy(result7, "", sizeof(result7)), result7);
    EXPECT_STREQ(result7, "");
}

TEST(StringFunction, strcat) {
    char result[20];
    result[0] = '\0';

    EXPECT_EQ(String::strcat(result, "Hello"), result);
    EXPECT_STREQ(result, "Hello");

    EXPECT_EQ(String::strcat(result, " World"), result);
    EXPECT_STREQ(result, "Hello World");

    EXPECT_EQ(String::strcat(result, ""), result);
    EXPECT_STREQ(result, "Hello World");

}


TEST(StringFunction, strncat) {
    char result[20]; // Initialize result with an empty string
    result[0] = '\0';

    EXPECT_EQ(String::strncat(result, "Hello World", 11), result); 
    EXPECT_STREQ(result, "Hello World");

    char original[20]; 
    strcpy(original, result);

    EXPECT_EQ(String::strncat(result, "!!!", 3), result); 
    EXPECT_STREQ(result, "Hello World!!!");

    strcpy(result, original);

    EXPECT_EQ(String::strncat(result, "", 1), result); 
    EXPECT_STREQ(result, "Hello World");

    EXPECT_EQ(String::strncat(result, "", 0), result); // Length 0 should change nothing
    EXPECT_STREQ(result, "Hello World");
}



TEST(StringFunction, strcmp) {
    const char source1[] = "Hello";
    const char source2[] = "Hello";
    const char source3[] = "World";
    const char source4[] = "";

    EXPECT_EQ(String::strcmp(source1, source2), 0);

    EXPECT_LT(String::strcmp(source1, source3), 0);

    EXPECT_GT(String::strcmp(source3, source1), 0);

    EXPECT_GT(String::strcmp(source3, source4), 0);
    EXPECT_LT(String::strcmp(source4, source3), 0);
    
    EXPECT_EQ(String::strcmp(source4, source4), 0);


}


TEST(StringFunction, strncmp) {
    const char source1[] = "Hello";
    const char source2[] = "World";
    const char source3[] = "Hello World";

    EXPECT_EQ(String::strncmp(source1, source1, 5), 0);

    EXPECT_LE(String::strncmp(source1, source2, 3), 0);

    EXPECT_EQ(String::strncmp(source1, source3, 5), 0);

    EXPECT_GT(String::strncmp(source1, "", 5), 0);

    EXPECT_EQ(String::strncmp(source1, source3, 5), 0);

    EXPECT_EQ(String::strncmp(source1, source2, 0), 0);
}



TEST(StringFunction, reverse_cpy) {
    const char source[] = "Hello";
    char result[6];
    const char oneChar[] = "A";
    const char empty[] = "";

    String::reverse_cpy(result, source);
    EXPECT_STREQ(result, "olleH");

    String::reverse_cpy(result, oneChar);
    EXPECT_STREQ(result, "A");

    String::reverse_cpy(result, empty);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strchr) {
    const char source[] = "Hello World";
    const char empty[] = "";

    EXPECT_TRUE(String::strchr(source, 'W') != nullptr);

    EXPECT_TRUE(String::strchr(source, 'Z') == nullptr);

    EXPECT_TRUE(String::strchr(empty, 'H') == nullptr);

    EXPECT_TRUE(String::strchr(source, '\0') == source + strlen(source));

    EXPECT_TRUE(String::strchr(empty, '\0') == empty);
}


TEST(StringFunction, strstr) {
    const char source[] = "Hello World";
    const char empty[] = "";

    EXPECT_TRUE(String::strstr(source, "World") != nullptr);

    EXPECT_TRUE(String::strstr(source, "Moon") == nullptr);

    EXPECT_TRUE(String::strstr(empty, "Hello") == nullptr);

    EXPECT_EQ(String::strstr(source, empty), source);
}
