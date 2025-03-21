#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'marsExploration' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int marsExploration(string s) {
    int cnt = 0;
    int pos = 0;
    for(char c : s) {
        if(pos == 3) pos = 0;
        if(c != 'S' && (pos == 0 || pos==2)) cnt++;
        if(c != 'O' && pos == 1) cnt++;
        pos++;
    }
    return cnt;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    int result = marsExploration(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
