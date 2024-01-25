#include "word_count.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void to_lowercase(string& str) {
    for (char& c : str) {
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
    }
}

set<string> load_stopwords(istream& stopword_stream) {
    set<string> stopwords;
    string word;
    while (stopword_stream >> word) {
        to_lowercase(word);
        stopwords.insert(word);
    }
    return stopwords;
}

map<string, int> count_words(istream& document_stream, const set<string>& stopwords) {
    map<string, int> word_counts;
    string word, subword;
    while (document_stream >> word) {
        to_lowercase(word);
        
        // Handle hyphenated words and remove non-alphabetic characters
        size_t start = 0, end = 0;
        while ((end = word.find_first_of(" -", start)) != string::npos) {
            if (end > start) { // Check if there is a non-empty subword
                subword = word.substr(start, end - start);
                if (stopwords.find(subword) == stopwords.end()) {
                    ++word_counts[subword];
                }
            }
            start = end + 1;
        }
        // Handle the last subword after the last hyphen (if any)
        if (start < word.length()) {
            subword = word.substr(start);
            if (stopwords.find(subword) == stopwords.end()) {
                ++word_counts[subword];
            }
        }
    }
    return word_counts;
}

void output_word_counts(const map<string, int>& word_counts, ostream& output_stream) {
    for (const auto& word_count : word_counts) {
        output_stream << word_count.first << ' ' << word_count.second << '\n';
    }
}
