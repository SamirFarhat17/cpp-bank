#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'anagram' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int anagram(string s) {
    if(s.length() % 2 != 0) return -1;
    
    std::string s1 = s.substr(0, s.length()/2);
    std::string s2 = s.substr(s.length()/2, s.length());
    std::cout << s1 << " " << s2 << "-\n";
    
    int changes = 0;
    
    std::unordered_map<char,int> freqMap1, freqMap2;
    
    for(char c : s1) freqMap1[c]++;
    for(char c : s2) freqMap2[c]++;
    for(auto it = freqMap2.begin(); it != freqMap2.end(); ++it) {
        if(freqMap1[it->first] > it->second ) continue;
        changes += std::abs(freqMap1[it->first] - it->second);
    }
    
    return changes;
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

        int result = anagram(s);

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
