#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'getWays' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. LONG_INTEGER_ARRAY c
 */
long ways = 0;

void permuteWays(int idx,long long sum, const std::vector<long>& coins, int target, 
        std::unordered_set<std::string>& uniqueCombs, std::string& currComb) {
    
    // If the sum equals the target, it's a valid combination.
    if (sum == target) {
        ways++;
        return;
    }

    // Iterate over each coin denomination and try to add it to the current combination.
    for (int i = idx; i < coins.size(); i++) {
        // Check if adding this coin doesn't exceed the target.
        if (sum + coins[i] <= target) {
            // Create a copy of currComb to avoid modifying the same string in multiple recursive calls.
            currComb[i]++; // Increment the count of the coin type in the combination.
            
            // If this combination is unique, recurse to find further combinations.
            if (uniqueCombs.find(currComb) == uniqueCombs.end()) {
                uniqueCombs.insert(currComb); // Mark this combination as used.
                permuteWays(i, sum + coins[i], coins, target, uniqueCombs, currComb);
            }
            currComb[i]--;
        }
    }
}

// Main function to get the number of ways to form the target sum using the available coins.
long getWaysSlow(int n, std::vector<long> c) {
    if (n == 0 || c.empty()) return 0; // If there's no target or no coins, return 0.

    std::string comb(c.size(), '0'); // Initialize a combination string of length equal to the number of coin types.
    std::unordered_set<std::string> uniqueCombs; // Set to store unique combinations.
    
    // Start the permutation process for each coin type.
    for (int i = 0; i < c.size(); i++) {
        if (c[i] <= n) {
            // Increment the coin count for this type and start the recursive search.
            comb[i] = '1'; // Start with one coin of this type.
            uniqueCombs.insert(comb); // Mark the initial combination.
            permuteWays(i, c[i], c, n, uniqueCombs, comb);
            comb[i] = '0'; // Reset the count of this coin type after the recursion.
        }
    }
    return ways;
}

long getWays(int n, std::vector<long>& c) {
    std::vector<long> dp(n + 1, 0);
    dp[0] = 1; // There is one way to make sum 0 (using no coins)

    // Process each coin type one by one
    for (long coin : c) {
        for (int amount = coin; amount <= n; amount++) {
            dp[amount] += dp[amount - coin]; // Build solutions iteratively
        }
    }

    return dp[n]; // The number of ways to make sum 'n'
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    string c_temp_temp;
    getline(cin, c_temp_temp);

    vector<string> c_temp = split(rtrim(c_temp_temp));

    vector<long> c(m);

    for (int i = 0; i < m; i++) {
        long c_item = stol(c_temp[i]);

        c[i] = c_item;
    }

    // Print the number of ways of making change for 'n' units using coins having the values given by 'c'

    long ways = getWays(n, c);

    fout << ways << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
