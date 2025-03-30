#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'equalStacks' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY h1
 *  2. INTEGER_ARRAY h2
 *  3. INTEGER_ARRAY h3
 */
void normalize(long& height1, long& height2, long& height3, std::queue<int>& s1, 
               std::queue<int>& s2, std::queue<int>& s3) {
    long maxim = std::max({height1, height2, height3});
    
    // Reduce stacks from the tallest
    if (height1 == maxim) {
        height1 -= s1.front();
        s1.pop();
    }
    else if (height2 == maxim) {
        height2 -= s2.front();
        s2.pop();
    }
    else {
        height3 -= s3.front();
        s3.pop();
    }
}

int equalStacks(std::vector<int> h1, std::vector<int> h2, std::vector<int> h3) {
    long height1 = 0, height2 = 0, height3 = 0;
    std::queue<int> s1, s2, s3;
    
    // Fill the stacks and calculate total height
    for (int x : h1) { s1.push(x); height1 += x; }
    for (int x : h2) { s2.push(x); height2 += x; }
    for (int x : h3) { s3.push(x); height3 += x; }
    
    // Normalize until the heights are equal or one of the stacks is empty
    while (height1 != height2 || height2 != height3) {
        normalize(height1, height2, height3, s1, s2, s3);
        if (height1 == 0 || height2 == 0 || height3 == 0) break;
    }
    
    return std::min({height1,height2, height3}); // return the common height (all heights should be equal at this point)
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n1 = stoi(first_multiple_input[0]);

    int n2 = stoi(first_multiple_input[1]);

    int n3 = stoi(first_multiple_input[2]);

    string h1_temp_temp;
    getline(cin, h1_temp_temp);

    vector<string> h1_temp = split(rtrim(h1_temp_temp));

    vector<int> h1(n1);

    for (int i = 0; i < n1; i++) {
        int h1_item = stoi(h1_temp[i]);

        h1[i] = h1_item;
    }

    string h2_temp_temp;
    getline(cin, h2_temp_temp);

    vector<string> h2_temp = split(rtrim(h2_temp_temp));

    vector<int> h2(n2);

    for (int i = 0; i < n2; i++) {
        int h2_item = stoi(h2_temp[i]);

        h2[i] = h2_item;
    }

    string h3_temp_temp;
    getline(cin, h3_temp_temp);

    vector<string> h3_temp = split(rtrim(h3_temp_temp));

    vector<int> h3(n3);

    for (int i = 0; i < n3; i++) {
        int h3_item = stoi(h3_temp[i]);

        h3[i] = h3_item;
    }

    int result = equalStacks(h1, h2, h3);

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
