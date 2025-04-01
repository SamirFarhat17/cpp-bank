#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'weightedUniformStrings' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. STRING s
 *  2. INTEGER_ARRAY queries
 */
int computeWeight(std::string str) {
    int sum = 0;
    for(char c : str) {
        sum += (c - ('a'-1));
    }
    return sum;
}

vector<string> weightedUniformStrings(string s, vector<int> queries) {
    std::unordered_set<int> validWeights;
    std::string substr = "";
    for(char c : s) {
        if(substr.empty() || c == substr[substr.size()-1]) {
            substr += c;
            validWeights.insert(computeWeight(substr));
        }
        else {
            substr = c;
            validWeights.insert(c - ('a'-1));
        }
        
    }
    
    std::vector<std::string> res;
    for(int q : queries) {
        if(validWeights.find(q) != validWeights.end()) res.push_back("Yes");
        else res.push_back("No");
    }
    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string queries_count_temp;
    getline(cin, queries_count_temp);

    int queries_count = stoi(ltrim(rtrim(queries_count_temp)));

    vector<int> queries(queries_count);

    for (int i = 0; i < queries_count; i++) {
        string queries_item_temp;
        getline(cin, queries_item_temp);

        int queries_item = stoi(ltrim(rtrim(queries_item_temp)));

        queries[i] = queries_item;
    }

    vector<string> result = weightedUniformStrings(s, queries);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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
