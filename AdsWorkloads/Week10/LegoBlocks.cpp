#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'legoBlocks' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 */
#include <iostream>
#include <vector>
#include <unordered_map>

const std::vector<int> blocks = {1, 2, 3, 4};

void permute(std::vector<bool> prevRep, int width, int curr, std::string currFloor, std::vector<std::string>& res) {
    if (curr == width) {
        res.push_back(currFloor);
        return;
    }

    for (int b : blocks) {
        if (curr + b <= width && !prevRep[curr + b]) {
            prevRep[curr + b] = true;  // Mark the block position
            permute(prevRep, width, curr + b, currFloor + std::to_string(b), res);
            prevRep[curr + b] = false; // Unmark for backtracking
        }
    }
}

std::vector<std::string> computeValidFloors(const std::string& prevFloor, int width) {
    std::vector<std::string> res;
    std::vector<bool> prevRep(width+1, false);
    int cloister = 0;

    for (char c : prevFloor) {
        cloister += c - '0';
        prevRep[cloister] = true;
    }
    prevRep[width] = false;

    for (int b : blocks) {
        if (!prevRep[b]) {  // Ensure starting block is valid
            std::string currFloor = std::to_string(b);
            permute(prevRep, width, b, currFloor, res);
        }
    }
    return res;
}

void permutes(int width, std::unordered_map<int, std::vector<std::string>>& layer, int idx) {
    std::cout << "[LAYER]" << '\n';
    for (const std::string& l : layer[idx]) {
        std::vector<std::string> validFloors = computeValidFloors(l, width);
        std::cout << "BASE : " << l << '\n';
        for (const std::string& validFloor : validFloors) {
            std::cout << validFloor << '\n';
            layer[idx + 1].push_back(validFloor);
        }
    }
}

int legoBlocksAlt(int n, int m) {
    std::cout << "[TESTCASE]" << '\n';
    std::unordered_map<int, std::vector<std::string>> res;
    res[0] = {""};
    for (int i = 0; i < n; i++) {
        permutes(m, res, i);
    }
    return res[n].size();
}

// MODULO * MODULO < UINT64_MAX
constexpr uint64_t MODULO = 1'000'000'007;
static_assert(numeric_limits<uint64_t>::max() / MODULO >= MODULO, "");

uint64_t modulopow(uint64_t x, uint64_t c) {
    x = x % MODULO;
    uint64_t out = 1;
    for (uint64_t i = 0; i < c; ++i) {
        out *= x;
        out %= MODULO;
    }
    return out;
}

uint64_t legoBlocks(int height, int width) {
    vector<uint64_t> row = { 1, 1, 2, 4 };
    for (int i = 4; i <= width; ++i) {
        uint64_t sum = row[i - 1]
                 + row[i - 2]
                 + row[i - 3]
                 + row[i - 4];
        row.push_back(sum % MODULO);
    }

    vector<uint64_t> total;
    for (int i = 0; i <= width; ++i) {
        total.push_back(modulopow(row[i], height));
    }

    vector<uint64_t> stable = {1};
    for (int i = 1; i <= width; ++i) {
        uint64_t unstable = 0;
        for (int j = 1; j < i; ++j) {
            // Avoid double-counting unstable configurations
            unstable += (stable[j] * total[i - j]) % MODULO;
            unstable %= MODULO;
        }
        stable.push_back((total[i] - unstable + MODULO) % MODULO);
    }
    return stable[width];
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        int result = legoBlocks(n, m);

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
