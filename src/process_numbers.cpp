#include "process_numbers.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std


void split_odd_even(std::istream& numbers, std::ostream& odds, std::ostream& evens) {
    using namespace std;
    vector<int> nums((istream_iterator<int>(numbers)), istream_iterator<int>());
    
    sort(nums.begin(), nums.end());
    
    copy_if(nums.begin(), nums.end(), ostream_iterator<int>(odds, " "), [](int n) { return n % 2 != 0; });
    odds << '\n';
    copy_if(nums.begin(), nums.end(), ostream_iterator<int>(evens, "\n"), [](int n) { return n % 2 == 0; });
}