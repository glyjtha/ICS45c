#include <gtest/gtest.h>

#include <sstream>
#include "word_count.hpp"

using namespace std;

TEST(WordCount, ToLowercase){
	string empty = "";
    to_lowercase(empty);
    EXPECT_EQ(empty, "");

    string lower = "lowercase";
    to_lowercase(lower);
    EXPECT_EQ(lower, "lowercase");
}

TEST(WordCount, LoadStopWords){
	stringstream emptyStream("");
	
	const auto stopwords = load_stopwords(emptyStream);

    EXPECT_TRUE(stopwords.empty());

    stringstream specialCharsStream("! @ # $ %");
    const auto stopwords2 = load_stopwords(specialCharsStream);
    EXPECT_EQ(stopwords2.size(), 5);
    EXPECT_TRUE(stopwords2.find("!") != stopwords2.end());

}

TEST(WordCount, CountWords){
	stringstream emptyStream;
    const auto stopwords = load_stopwords(emptyStream);
    EXPECT_TRUE(stopwords.empty());

	stringstream stream("stop stop stop");
    const auto stopwords2 = load_stopwords(stream);
    EXPECT_EQ(stopwords2.size(), 1);
    EXPECT_TRUE(stopwords2.find("stop") != stopwords2.end());

}

TEST(WordCount, OutputWordCounts) {
	map<string, int> emptyWordCounts;
    ostringstream outputStream;
    output_word_counts(emptyWordCounts, outputStream);
    EXPECT_TRUE(outputStream.str().empty());

}
