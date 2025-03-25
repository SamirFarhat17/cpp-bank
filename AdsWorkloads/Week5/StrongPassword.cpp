#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'minimumNumber' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. STRING password
 */

int minimumNumber(int n, string password) {
    // Return the minimum number of characters to make the password strong
    bool digit = false;
    bool lowercase = false;
    bool uppercase = false;
    bool special = false;
    
    unordered_set<char> specials = {'!','@','#','$','%','^','&','*','(',')','-','+'};
    for(char c : password){
        if(std::isdigit(c)) digit = true;
        else if(c <= 'z' && c >= 'a') lowercase = true;
        else if(c <= 'Z' && c >= 'A') uppercase = true;
        else if(specials.find(c) != specials.end()) special = true;
    }
    
    int count = 0;
    if(!digit) count++;
    if(!lowercase) count++;
    if(!uppercase) count++;
    if(!special) count++;
    int remainingLen = std::max(0,  6 - static_cast<int>(password.size()));
    
    return (remainingLen > count) ? remainingLen : count;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string password;
    getline(cin, password);

    int answer = minimumNumber(n, password);

    fout << answer << "\n";

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
