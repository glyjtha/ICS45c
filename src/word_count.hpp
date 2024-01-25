#ifndef WORD_COUNT_HPP
#define WORD_COUNT_HPP

#include <iosfwd>
#include <string>
#include <set>
#include <map>

void to_lowercase(std::string& str);

std::set<std::string> load_stopwords(std::istream& stopword_stream);

std::map<std::string, int> count_words(std::istream& document_stream, const std::set<std::string>& stopwords);

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output_stream);

#endif
