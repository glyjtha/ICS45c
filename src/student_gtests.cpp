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

	string mixed = "LoWeR&UPPER";
    to_lowercase(mixed);
    EXPECT_EQ(mixed, "lower&upper");
}

TEST(WordCount, LoadStopWords){
	stringstream emptyStream("");
	const auto stopwords = load_stopwords(emptyStream);
    EXPECT_TRUE(stopwords.empty());

    stringstream specialCharsStream("! @ # $ %");
    const auto stopwords2 = load_stopwords(specialCharsStream);
    EXPECT_EQ(stopwords2.size(), 5);
    EXPECT_TRUE(stopwords2.find("!") != stopwords2.end());

	stringstream repeatedWordsStream("the the and and the");
    const auto stopwords3 = load_stopwords(repeatedWordsStream);
    EXPECT_EQ(stopwords3.size(), 2);
    EXPECT_TRUE(stopwords3.find("the") != stopwords3.end());
    EXPECT_TRUE(stopwords3.find("and") != stopwords3.end());

	stringstream caseStream("The THE the");
    const auto stopwords4 = load_stopwords(caseStream);
    EXPECT_EQ(stopwords4.size(), 1);
    EXPECT_TRUE(stopwords4.find("the") != stopwords4.end());

	stringstream spaceStream(" the   and \n");
    const auto stopwords5 = load_stopwords(spaceStream);
    EXPECT_EQ(stopwords5.size(), 2);
    EXPECT_TRUE(stopwords5.find("the") != stopwords5.end());
    EXPECT_TRUE(stopwords5.find("and") != stopwords5.end());
	
	stringstream nonAlphaStream("don't can't");
    const auto stopwords6 = load_stopwords(nonAlphaStream);
    EXPECT_EQ(stopwords6.size(), 2);
    EXPECT_TRUE(stopwords6.find("don't") != stopwords6.end());
    EXPECT_TRUE(stopwords6.find("can't") != stopwords6.end());


}

TEST(WordCount, CountWords){
	stringstream emptyStream;
    set<string> stopwords;
    const auto wordCounts = count_words(emptyStream, stopwords);
    EXPECT_TRUE(wordCounts.empty());

	stringstream stream("Word word WoRd");
    set<string> stopwords1;
    const auto wordCounts1 = count_words(stream, stopwords1);
    EXPECT_EQ(wordCounts1.size(), 1);

	stringstream stream1("word1, word2! word3?");
    set<string> stopwords2;
    const auto wordCounts2 = count_words(stream1, stopwords2);
    EXPECT_EQ(wordCounts2.size(),3);

	stringstream stream2("word1 1234 word2 5678");
    set<string> stopwords4;
    const auto wordCounts4 = count_words(stream2, stopwords4);
    EXPECT_EQ(wordCounts4.size(),4);



}

TEST(WordCount, OutputWordCounts) {
	map<string, int> emptyWordCounts;
    ostringstream outputStream;
    output_word_counts(emptyWordCounts, outputStream);
    EXPECT_TRUE(outputStream.str().empty());

	map<string, int> wordCounts{{"word1", 1}, {"word2", 2}};
    ostringstream outputStream1;
    output_word_counts(wordCounts, outputStream1);
    string expectedOutput = "word1 1\nword2 2\n";
    EXPECT_EQ(outputStream1.str(), expectedOutput);

	map<string, int> wordCounts2{{"word1!", 1}, {"word2#", 2}};
    ostringstream outputStream2;
    output_word_counts(wordCounts2, outputStream2);
    string expectedOutput2 = "word1! 1\nword2# 2\n";
    EXPECT_EQ(outputStream2.str(), expectedOutput2);

	map<string, int> wordCounts3{{"apple", 2}, {"banana", 3}};
    ostringstream outputStream3;
    output_word_counts(wordCounts3, outputStream3);
    string expectedOutput3 = "apple 2\nbanana 3\n"; // Assuming alphabetical order
    EXPECT_EQ(outputStream3.str(), expectedOutput3);
	
	map<string, int> wordCounts4{{"word1", 1000}, {"word2", 2000}};
    ostringstream outputStream4;
    output_word_counts(wordCounts4, outputStream4);
    string expectedOutput4 = "word1 1000\nword2 2000\n";
    EXPECT_EQ(outputStream4.str(), expectedOutput4);

	map<string, int> wordCounts5{{"word1", 0}, {"word2", 0}};
    ostringstream outputStream5;
    output_word_counts(wordCounts5, outputStream5);
    string expectedOutput5 = "word1 0\nword2 0\n"; // Check if this is the expected behavior
    EXPECT_EQ(outputStream5.str(), expectedOutput5);

}
