#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'superReducedString' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string superReducedString(string s) {
    if(s.length() < 2) return s;
    int idx = 0;
    while(idx < static_cast<int>(s.length()) - 1) {
        if(s[idx] == s[idx+1]) {
            std::cout << s << std::endl;
            if(s.length() == 2) return "Empty String";
            s = s.substr(0,idx) + s.substr(idx+2, s.length());
            idx = 0;
            continue;
        }
        idx++;
    }
    return s;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = superReducedString(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
