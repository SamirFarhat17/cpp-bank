#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'maxMin' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY arr
 */
 
void merge(vector<int>& a1, vector<int>& a2, vector<int>& arr) {
    int l = 0, r = 0, k = 0;
    
    while(l < a1.size() && r < a2.size()) {
        if(a1[l] < a2[r]) arr[k++] = a1[l++];
        else arr[k++] = a2[r++];
    }
    
    while(l < a1.size()) arr[k++] = a1[l++];
    while(r < a2.size()) arr[k++] = a2[r++];
    
}
 
void mergeSort(vector<int>& arr) {
    int n = arr.size();
    if(n < 2) return;
    
    int mid = arr.size()/2;
    
    std::vector<int> a1, a2;
    
    for(int i = 0; i < mid; i++) a1.push_back(arr[i]);
    for(int i = mid; i < arr.size(); i++) a2.push_back(arr[i]);
    
    mergeSort(a1);
    mergeSort(a2);
    merge(a1, a2, arr);
}

int maxMin(int k, vector<int> arr) {
    if(arr.empty() || k > arr.size()) return -1;
    
    mergeSort(arr);
    int minUnfairness = INT_MAX;
    
    for(size_t i = 0; i <= arr.size() - k; i++) {
        minUnfairness = std::min(minUnfairness, arr[i+k-1] - arr[i]);
    }
    
    
    return minUnfairness;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string k_temp;
    getline(cin, k_temp);

    int k = stoi(ltrim(rtrim(k_temp)));

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        string arr_item_temp;
        getline(cin, arr_item_temp);

        int arr_item = stoi(ltrim(rtrim(arr_item_temp)));

        arr[i] = arr_item;
    }

    int result = maxMin(k, arr);

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
