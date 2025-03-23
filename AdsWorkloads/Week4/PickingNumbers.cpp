#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'pickingNumbers' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY a as parameter.
 */

int pickingNumbers(vector<int> a) {
    std::unordered_map<int, int> freqMap;
    int maxim = 0;
    
    for(int n : a) freqMap[n]++;
    
    for(auto it = freqMap.begin(); it != freqMap.end(); ++it) {
        int cas = it->first;
        if(freqMap.find(cas-1) != freqMap.end()) maxim = std::max(maxim, freqMap[cas] + freqMap[cas - 1]);
        else  maxim = std::max(maxim, freqMap[cas]);    
    }
    
    return maxim;
}
int pickingNumbersSlow(vector<int> a) {
    if(a.size() <= 1) return 0;
    int maxim = 0;
    int lc;
    int uc;
    bool* visits = new bool[a.size()]();
    
    for(int i = 0; i < a.size(); i++) {
        lc = 0;
        uc = 0;
        for(int j = i; j < a.size(); j++) {
            if(std::abs(a[i]-a[j]) <= 1) {
                if(a[j] < a[i]) lc++;
                else if(a[j] > a[i]) uc++;
                else {
                    uc++;
                    lc++;
                }
            } 
        }
        uc = std::max(uc, lc);
        maxim = std::max(maxim, uc);
    }
    
    delete[] visits;
    
    
    return maxim;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string a_temp_temp;
    getline(cin, a_temp_temp);

    vector<string> a_temp = split(rtrim(a_temp_temp));

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        int a_item = stoi(a_temp[i]);

        a[i] = a_item;
    }

    int result = pickingNumbers(a);

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
