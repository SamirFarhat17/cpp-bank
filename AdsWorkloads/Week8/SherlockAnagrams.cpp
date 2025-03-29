#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'sherlockAndAnagrams' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

int sherlockAndAnagrams(std::string s) {
    std::unordered_map<std::string, int> freqMap;
    int count = 0;
    
    // Generate all substrings
    for (size_t i = 0; i < s.length(); i++) {
        std::string sub = "";
        std::vector<int> charCount(26, 0);
        
        for (size_t j = i; j < s.length(); j++) {
            charCount[s[j] - 'a']++;  // Track frequency
            std::string key = "";
            
            // Convert frequency array to a hashable string key
            for (int k = 0; k < 26; k++) {
                key += std::to_string(charCount[k]) + "#";
            }
            
            freqMap[key]++;
        }
    }
    // Count pairs from frequency map
    for (auto it = freqMap.begin(); it != freqMap.end(); ++it) {
        count += (it->second * (it->second - 1)) / 2; // nC2 combinations
    }
    
    return count;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = sherlockAndAnagrams(s);

        fout << result << "\n";
    }

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
