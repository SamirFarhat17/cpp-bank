#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'pangrams' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string pangrams(string s) {
    int* alpha = new int[26]();
    bool pangram = true;
    
    for(char c : s) {
        alpha[std::tolower(c) - 'a']++;
    }
    
    for(int i = 0; i < 26; i++) {
        if(alpha[i] == 0) pangram = false;
    }
    delete[] alpha;
    
    return (pangram) ? "pangram" : "not pangram";
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = pangrams(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
