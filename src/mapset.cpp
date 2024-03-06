#include "mapset.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std

string to_lowercase(const std::string& str){
    string lower_str;
    transform(str.begin(), str.end(), back_inserter(lower_str),
        [](unsigned char c){ return tolower(c); });
    return lower_str;
}

set<string> load_stopwords(istream& stopwords_stream) {
    set<string> stopwords;
    string word;
    while (stopwords_stream >> word) {
        stopwords.insert(to_lowercase(word));
    }
    return stopwords;
}

map<string, int> count_words(istream& document, const set<string>& stopwords){
    map<string, int> word_counts;
    string word;
    while(document >> word){
        word = to_lowercase(word);
        if(stopwords.find(word) == stopwords.end()){
            ++word_counts[word];
        }
    }
    return word_counts;
}

void output_word_counts(const map<string, int>& word_counts, ostream& output){
    for (const auto& [word, count] : my_map){
        cout << word << count;
    }
}
