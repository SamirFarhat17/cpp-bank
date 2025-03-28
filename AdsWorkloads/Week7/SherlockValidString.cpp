#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'isValid' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string isValid(string s) {
    std::unordered_map<char,int> freqMap;
    std::unordered_map<int, int> freqFreqs;
    
    for(char c : s) freqMap[c]++;
    
    for(auto it = freqMap.begin(); it != freqMap.end(); ++it) {
        freqFreqs[it->second]++;
    }
    
    if(freqFreqs.size() == 1) return "YES";
    else if(freqFreqs.size() > 2) return "NO";
    
    auto it = freqFreqs.begin();
    int f1 = it->first, c1 = it->second;  // First frequency and count
    it++;
    int f2 = it->first, c2 = it->second;  // Second frequency and count
    if ((f1 == 1 && c1 == 1) || (f2 == 1 && c2 == 1)) return "YES";
    
    // The frequencies must differ by exactly 1, and the higher one should occur once
    if ((std::abs(f1 - f2) == 1) && ((f1 > f2 && c1 == 1) || (f2 > f1 && c2 == 1))) return "YES";
    
    return "NO";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
