#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

// Comparator class with static method
struct Comparator {
    static bool compareBigInt(const std::string& s1, const std::string& s2) {
        // First, compare the lengths
        if (s1.length() != s2.length()) {
            return s1.length() < s2.length();  // shorter length means smaller number
        }
        
        // If lengths are the same, compare lexicographically
        return s1 < s2;
    }
};

// Function to sort big integers represented as strings
std::vector<std::string> bigSorting(std::vector<std::string> unsorted) {
    std::sort(unsorted.begin(), unsorted.end(), 
        [](const std::string& s1, const std::string& s2) {
            return Comparator::compareBigInt(s1, s2);
        }
    );
    return unsorted;
}

int main() {
    // Test case with large numbers
    std::vector<std::string> unsorted = {"999999999", "1000000000", "123456789", "987654321"};
    std::vector<std::string> sorted = bigSorting(unsorted);

    // Output the sorted result
    for (const auto& str : sorted) {
        std::cout << str << std::endl;
    }

    return 0;
}
