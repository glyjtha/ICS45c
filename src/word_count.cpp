#include "word_count.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void to_lowercase(string& str) {
	for (char& c : str) {
        if (c >= 'A' && c <= 'Z') {
            c += 'a' - 'A';
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
    string word;
    while (document_stream >> word) {
        // Convert to lowercase
        to_lowercase(word);
        
        // Remove any non-alphabetic characters from the end of the word
        word.erase(std::remove_if(word.begin(), word.end(),
                                  [](char c) { return !isalpha(c) && c != '-'; }), word.end());

        if (!word.empty() && stopwords.find(word) == stopwords.end()) {
            ++word_counts[word];
        }
    }
    return word_counts;
}

void output_word_counts(const map<string, int>& word_counts, ostream& output_stream) {
    for (const auto& word_count : word_counts) {
        output_stream << word_count.first << ' ' << word_count.second << '\n';
    }
}
