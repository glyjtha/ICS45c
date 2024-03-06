#include "process_numbers.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

void split_odd_even(std::istream& numbers, std::ostream& odds, std::ostream& evens) {
    std::vector<int> nums((std::istream_iterator<int>(numbers)), std::istream_iterator<int>());
    
    std::sort(nums.begin(), nums.end());
    
    std::copy_if(nums.begin(), nums.end(), std::ostream_iterator<int>(odds, " "), [](int n) { return n % 2 != 0; });
    odds << std::endl;  
    std::copy_if(nums.begin(), nums.end(), std::ostream_iterator<int>(evens, "\n"), [](int n) { return n % 2 == 0; });
}
