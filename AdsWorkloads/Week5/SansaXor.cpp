#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'sansaXor' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

std::ostream& operator<<(ostream& os, const std::vector<int> arr) {
    for(int n : arr) {
        os << n << ' ';
    }
    return os;
}

void permute(std::vector<std::vector<int>>& res, int idx, std::vector<int> arr, std::vector<int> temp) {
    temp.push_back(arr[idx]);
    res.push_back(temp);
    if(temp.size() == arr.size()) return;
    
    if(idx == arr.size()-1) return;
    else idx++;
    
    permute(res, idx, arr, temp);
    
}

std::vector<std::vector<int>> permutations(std::vector<int>& arr) {
    std::vector<std::vector<int>> res;
    if(arr.empty()) return res;
    if(arr.size() == 1) {
        res.push_back({arr[0]});
        return res;
    }
    
    for(int i = 0; i < arr.size(); i++) {
        std::vector<int> temp;
        permute(res, i, arr, temp);
    }
    
    return res;
}
 

int sansaXor2(vector<int> arr) {
    std::vector<std::vector<int>> continguousSubarrays = permutations(arr);
    
    int res = -1;
    for(std::vector<int> arr : continguousSubarrays) {
        for(int n : arr) {
            if(res == -1) res = n;
            else res ^= n;
        }
    }
    
    return res;
}

int sansaXor(vector<int> arr) {
    int res = 0;
    int n = arr.size();

    if (n % 2 == 0) return 0; // If n is even, XOR of all subarrays is 0

    for (int i = 0; i < n; i += 2) {
        res ^= arr[i]; // Only XOR elements at odd positions (0-based index)
    }

    return res;
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

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split(rtrim(arr_temp_temp));

        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        int result = sansaXor(arr);

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
