#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'counterGame' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts LONG_INTEGER n as parameter.
 */

bool isPowerOfTwo(long n) {
    return (n & (n - 1)) == 0; // Power of 2 has only one '1' bit in binary
}

long largestPowerOfTwo(long n) {
    long power = 1;
    while (power * 2 <= n) {
        power *= 2;
    }
    return power;
}

std::string counterGame(long n) {
    bool louiseTurn = true; // Louise starts first

    while (n > 1) {
        if (isPowerOfTwo(n)) {
            n /= 2;
        } else {
            n -= largestPowerOfTwo(n);
        }
        louiseTurn = !louiseTurn; // Alternate turns
    }
    
    return (louiseTurn) ? "Richard" : "Louise";
}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(cin, n_temp);

        long n = stol(ltrim(rtrim(n_temp)));

        string result = counterGame(n);

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
