#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'permutationGame' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */
int xorSum(std::vector<int> arr) {
    int sum = 0;
    for(int a : arr) sum ^= a;
    return sum;
}

unordered_map<string, bool> memo;

bool isIncreasing(vector<int> arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i+1]) return false;
    }
    return true;
}

bool findWinner(vector<int> arr) {
    string key = "";
    for(int n : arr) key += std::to_string(n);
    
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }
    if (isIncreasing(arr)) {
        memo[key] = true;
        return true;
    }
    for (int i = 0; i < arr.size(); i++) {
        std::vector<int> newArr;
        newArr.reserve(arr.size() - 1); // Reserve space for efficiency

        // Copy elements before index i
        newArr.insert(newArr.end(), arr.begin(), arr.begin() + i);

        // Copy elements after index i
        newArr.insert(newArr.end(), arr.begin() + i + 1, arr.end());
        if (findWinner(newArr)) {
            memo[key] = false;
            return false;
        }
    }
    memo[key] = true;
    return true;
}

string permutationGame(vector<int> arr) {
    // Write your code here
    memo.clear();
    return findWinner(arr) ? "Bob" : "Alice";

}



int main() {
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string arr_count_temp;
        getline(cin, arr_count_temp);

        int arr_count = stoi(ltrim(rtrim(arr_count_temp)));

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split(rtrim(arr_temp_temp));

        vector<int> arr(arr_count);

        for (int i = 0; i < arr_count; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        string result = permutationGame(arr);

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
