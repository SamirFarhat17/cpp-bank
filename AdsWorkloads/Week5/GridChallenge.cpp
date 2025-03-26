#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'gridChallenge' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING_ARRAY grid as parameter.
 */
 
void mergeStr(std::string& str, std::string& lStr,std::string& rStr) {
    int l = 0, r = 0, k = 0;
    
    while(l < lStr.length() && r < rStr.length()) {
        if(lStr[l] < rStr[r]) str[k++] = lStr[l++];
        else str[k++] = rStr[r++];
    }
    
    while(l < lStr.length()) str[k++] = lStr[l++];
    while(r < rStr.length()) str[k++] = rStr[r++];
}
 
void stringSort(std::string& str) {
    int n = str.length();
    if(n < 2) return;
    
    int mid = str.length()/2;
    std::string lStr = "";
    std::string rStr = "";
    for(int i = 0; i < mid; i++) lStr += str[i];
    for(int i = mid; i < str.length(); i++) rStr += str[i];
    
    stringSort(lStr);
    stringSort(rStr);
    mergeStr(str, lStr,rStr);
}

string gridChallenge(vector<string> grid) {
    if(grid.size() <= 1) return "YES";
    
    int prev = grid[0].length();
    for(int i = 0; i < grid.size(); i++) {
        if(grid[i].length() != prev) return "NO";
        stringSort(grid[i]);
        prev = grid[i].length();
    }
    
    for(int col = 0; col < grid[0].length(); col++) {
        for(int row = 0; row < grid.size()-1; row++) {
            if(grid[row][col] > grid[row+1][col]) return "NO";
        }
    }
    
    return "YES";
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

        int n = stoi(ltrim(rtrim(n_temp)));

        vector<string> grid(n);

        for (int i = 0; i < n; i++) {
            string grid_item;
            getline(cin, grid_item);

            grid[i] = grid_item;
        }

        string result = gridChallenge(grid);

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
