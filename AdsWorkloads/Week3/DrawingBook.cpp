#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'pageCount' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER p
 */

int pageCount(int n, int p) {
    bool even = (n % 2); // if even 2 pages on last 
    if(p == 0 || p == n || (p == n-1 && even)) return 0;
    
    // if 8 and searching from end 4 1:8,7 | 2:6,5 | 3:4,3
    // if 8 and searching from start 4 1:1 | 2:2,3 | 3:3,4
    // if 9 and searching 4, from end 1:9 | 2: 8,7 | 3:6,5 | 4: 5,4
    // if 9 and searching 4, from start 1:1 | 2:2,3 | 3:4,5
    // 23 page 11, 1:23 | 2:22,21 | 3:20,19 | 4:18,17 | 5:16,15 | 6:14,13 | 7:12,11
    int leftStart = (p/2);
    int rightStart = (n/2) - (p/2);
    
    return std::min(leftStart, rightStart);
    
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string p_temp;
    getline(cin, p_temp);

    int p = stoi(ltrim(rtrim(p_temp)));

    int result = pageCount(n, p);

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
