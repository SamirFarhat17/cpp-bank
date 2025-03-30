#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'alternate' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

 
void remove(std::string& str, std::unordered_set<char>& toRemove) {
    
    int idx = 0;
    for(char c : str) {
        if(!toRemove.count(c)) {
            str[idx] = c;
            idx++;
        }
    }
    str.resize(idx);
}

int alternate2(string s) {
    if(s.length() <= 1) return s.length();
    std::unordered_set<char> toRemove;
    int freqs[26] = {0};
    
    for(int i = 0; i < s.length(); i++) {
        freqs[s[i] - 'a']++;
        if(i != s.length() - 1) {
            if(s[i] == s[i+1]) toRemove.insert(s[i]);\
        }
    }
    
    for(int i = 0; i < 26; i++) {
        if(freqs[i] == 1) toRemove.insert(static_cast<char>(i + 'a'));
    }
    remove(s, toRemove);
    goto initialLoop;
    
    while(!toRemove.empty()){
        
initialLoop:

        std::cout << s << '\n';
        if(s.length() <= 1) return s.length();
        memset(freqs, 0, sizeof(freqs));
        toRemove.clear();
        
        for(int i = 0; i < s.length(); i++) {
            freqs[s[i] - 'a']++;
            if(i != s.length() - 1) {
                if(s[i] == s[i+1]) toRemove.insert(s[i]);
            }
        }
        remove(s, toRemove);
    }
    
    
    std::unordered_set<char> uniques;
    for(char c : s)  uniques.insert(c);
    
    return s.length();
}

// Function to check if a string alternates properly
bool isValidAlternate(const string& s, char first, char second) {
    char lastChar = '\0';
    for (char c : s) {
        if (c != first && c != second) continue; // Ignore characters not in the pair
        if (c == lastChar) return false; // Check for consecutive duplicates
        lastChar = c;
    }
    return true;
}

// Function to determine the longest alternating string possible
int alternate(const string& s) {
    set<char> uniqueChars(s.begin(), s.end()); // Extract unique characters
    vector<char> chars(uniqueChars.begin(), uniqueChars.end());
    
    int maxLength = 0;
    
    // Try all pairs of characters
    for (size_t i = 0; i < chars.size(); i++) {
        for (size_t j = i + 1; j < chars.size(); j++) {
            char first = chars[i], second = chars[j];
            if (isValidAlternate(s, first, second)) {
                // Count length of valid alternating string
                int length = 0;
                for (char c : s) {
                    if (c == first || c == second) length++;
                }
                maxLength = max(maxLength, length);
            }
        }
    }
    
    return maxLength;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string l_temp;
    getline(cin, l_temp);

    int l = stoi(ltrim(rtrim(l_temp)));

    string s;
    getline(cin, s);

    int result = alternate(s);

    fout << result << "\n";

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
