#include <bits/stdc++.h>
#include <cinttypes>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'palindromeIndex' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */
bool isPalindrome(std::string str) {
    for(int i = 0 ; i < str.length()/2; i++) {
        if(str[i] != str[str.length()-1-i]) return false;
    }
    
    return true;
}

int palindromeIndexAlt(string s) {
    if(isPalindrome(s)) return -1;
    if(s.length() <= 1) return -1;
    vector<std::string> rightPass(s.length());
    std::string currRPass = "";
    
    for(int i = s.length()-1; i >= 0; i--) {
        rightPass[i] = currRPass;
        currRPass = s[i] + currRPass;
    }
    
    std::string currLPass = "";
    //std::cout << "[TESTCASE]\n";
    for(int i = 0; i < s.length(); i++) {
        //std::printf("rPass is: %s and lPass is %s\n", rightPass[i].c_str(), currLPass.c_str());
        if(isPalindrome(currLPass + rightPass[i])) return i;
        currLPass += s[i];
    }
    
    return -1;
}

bool isPalindrome(const std::string& str, int left, int right) {
    while (left < right) {
        if (str[left] != str[right]) return false;
        left++;
        right--;
    }
    return true;
}

int palindromeIndex(std::string s) {
    int left = 0, right = s.length() - 1;
    
    while (left < right) {
        if (s[left] != s[right]) {
            // Check by removing the left character
            if (isPalindrome(s, left + 1, right)) return left;
            // Check by removing the right character
            if (isPalindrome(s, left, right - 1)) return right;
            
            return -1; // If neither removal makes it a palindrome
        }
        left++;
        right--;
    }
    
    return -1; // Already a palindrome
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = palindromeIndex(s);

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
