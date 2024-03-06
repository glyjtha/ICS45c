#include "mapset.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;

string to_lowercase(const std::string& str){
    string lower_str;
    transform(str.begin(), str.end(), back_inserter(lower_str),
        [](unsigned char c){ return tolower(c); });
    return lower_str;
}

set<string> load_stopwords(istream& stopwords_stream) {
    istream_iterator<string> start(stopwords_stream), end;
    set<string> stopwords;
    transform(start, end, inserter(stopwords, stopwords.end()), to_lowercase);
    return stopwords;
}


map<string, int> count_words(istream& document, const set<string>& stopwords) {
    istream_iterator<string> start(document), end;
    map<string, int> word_counts;
    for_each(start, end, [&word_counts, &stopwords](const string& word) {
        string lower_word = to_lowercase(word);
        if (stopwords.find(lower_word) == stopwords.end()) {
            ++word_counts[lower_word];
        }
    });
    return word_counts;
}

void output_word_counts(const map<string, int>& word_counts, ostream& output){
    for (const auto& [word, count] : word_counts) {
        output << word << " " << count << '\n';
    }
}
