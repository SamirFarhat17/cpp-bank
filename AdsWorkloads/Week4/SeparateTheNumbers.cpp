#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'separateNumbers' function below.
 *
 * The function accepts STRING s as parameter.
 */
bool dfs(string& s, long long prev, size_t index) {
    if (index == s.length()) return true; // Successfully reached end of string

    long long num = 0;
    for (size_t i = index; i < s.length(); i++) {
        num = num * 10 + (s[i] - '0'); // Build the number digit by digit
        
        if (num == prev + 1 && dfs(s, num, i + 1)) {
            return true;
        }
        
        if (num > prev + 1) break; // No need to continue if we already exceeded
    }
    
    return false;
}

void separateNumbers(string s) {
    for (size_t len = 1; len <= s.length() / 2; len++) {
        string firstPart = s.substr(0, len);
        
        if (firstPart[0] == '0') continue; // Ignore numbers with leading zeros
        
        long long firstNum = stoll(firstPart);
        
        if (dfs(s, firstNum, len)) {
            cout << "YES " << firstNum << endl;
            return;
        }
    }
    
    cout << "NO" << endl;
}


int main()
{
    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        separateNumbers(s);
    }

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
