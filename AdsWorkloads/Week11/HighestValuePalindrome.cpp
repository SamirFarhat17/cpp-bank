#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'highestValuePalindrome' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING s
 *  2. INTEGER n
 *  3. INTEGER k
 */

string highestValuePalindrome(string s, int n, int k) {
    int required_changes = 0;
    // Calculate minimum changes needed to make palindrome
    for (int i = 0; i < n / 2; ++i) {
        if (s[i] != s[n - 1 - i]) {
            required_changes++;
        }
    }
    
    if (required_changes > k) {
        return "-1";
    }
    
    int extra_changes = k - required_changes;
    
    for (int i = 0; i < n / 2; ++i) {
        int j = n - 1 - i;
        if (s[i] != s[j]) {
            char max_char = max(s[i], s[j]);
            if (max_char != '9' && extra_changes >= 1) {
                s[i] = '9';
                s[j] = '9';
                extra_changes--;
            } else {
                s[i] = max_char;
                s[j] = max_char;
            }
            k--;
        } 
        else {
            // Both characters are same
            if (s[i] != '9' && extra_changes >= 2) {
                s[i] = '9';
                s[j] = '9';
                extra_changes -= 2;
            }
        }
    }
    
    // Handle middle character for odd length
    if (n % 2 == 1 && k > 0) {
        int mid = n / 2;
        if (s[mid] != '9' && extra_changes >= 1) {
            s[mid] = '9';
            extra_changes--;
        }
    }
    
    return s;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string s;
    getline(cin, s);

    string result = highestValuePalindrome(s, n, k);

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
