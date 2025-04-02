#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);


/*
 * Complete the 'almostSorted' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> findUnsortedSubarray(vector<int>& nums) {
    int n = nums.size();
    int start = 0, end = n - 1;
    
    // Find the first index where the order breaks
    while (start < n - 1 && nums[start] <= nums[start + 1]) {
        start++;
    }
    
    // Already sorted
    if (start == n - 1) {
        return {-1, -1};
    }
    
    // Find the last index where the order breaks
    while (end > 0 && nums[end] >= nums[end - 1]) {
        end--;
    }
    
    // Find min and max in the unsorted subarray
    int min_val = *min_element(nums.begin() + start, nums.begin() + end + 1);
    int max_val = *max_element(nums.begin() + start, nums.begin() + end + 1);
    
    // Expand start to left if needed
    while (start > 0 && nums[start - 1] > min_val) {
        start--;
    }
    
    // Expand end to right if needed
    while (end < n - 1 && nums[end + 1] < max_val) {
        end++;
    }
    
    return {start, end};
}

void almostSorted(vector<int> arr) {
    vector<int> indices = findUnsortedSubarray(arr);
    
    if (indices[0] == -1) {
        cout << "yes\n";
        return;
    }
    
    // Check if swap would work
    swap(arr[indices[0]], arr[indices[1]]);
    if (is_sorted(arr.begin(), arr.end())) {
        cout << "yes\nswap " << indices[0]+1 << " " << indices[1]+1 << "\n";
        return;
    }
    swap(arr[indices[0]], arr[indices[1]]); // swap back
    
    // Check if reverse would work
    reverse(arr.begin() + indices[0], arr.begin() + indices[1] + 1);
    if (is_sorted(arr.begin(), arr.end())) {
        cout << "yes\nreverse " << indices[0]+1 << " " << indices[1]+1 << "\n";
        return;
    }
    
    cout << "no\n";
}
int main()
{
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

    almostSorted(arr);

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
