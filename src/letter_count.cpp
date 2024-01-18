#include <iostream>
using namespace std;
#include "letter_count.hpp"

constexpr int N_CHARS = ('Z' - 'A'+1);

int main(){
	int counters[N_CHARS] = {};
	string line;
	while(getline(cin,line)){
		count(line,counters);
	}
	print_counts(counters,N_CHARS);
	return 0;

}
