#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'commonChild' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING s1
 *  2. STRING s2
 */

int commonChildPartial(string s1, string s2) {
    if(s1.empty() || s2.empty()) return 0;
    if(s1 == s2) return s1.length();
    
    int commonOrdering = 0;
    std::unordered_map<char, queue<int>> charFreq1;
    std::unordered_map<char, queue<int>> charFreq2;
    
    for(int i = 0; i < s1.length(); i++) {
        charFreq1[s1[i]].push(i);
    }
    for(int i = 0; i < s2.length(); i++) {
        charFreq2[s2[i]].push(i);
    }
    
    int lastIdx = 0;
    for(int i = 0; i < s1.length(); i++) {
        char c = s1[i];
        if(charFreq2.find(c) != charFreq2.end()) {
            std::printf("Analyzing char %c, lastIdx is %d\n", c, lastIdx);
            queue<int>* temp = &charFreq2[c];
            int currIdx = lastIdx;
            while(!temp->empty()) {
                if(temp->front() > lastIdx) {
                    currIdx = temp->front();
                    break;
                }
                temp->pop();
            }
            if(temp->empty()) continue;
            else {
                temp->pop();
                lastIdx = currIdx;
                commonOrdering++;
            }
        }
    }
    
    return commonOrdering;
}

int commonChild(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();
    
    // ABCD
    //A00000
    //B01000
    //D00230
    //C00330
    // 00003
    // Create a DP table with (m+1) x (n+1) dimensions
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    // Build the DP table bottom-up
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    return dp[m][n];
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s1;
    getline(cin, s1);

    string s2;
    getline(cin, s2);

    int result = commonChild(s1, s2);

    fout << result << "\n";

    fout.close();

    return 0;
}
