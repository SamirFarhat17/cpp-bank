#include <bits/stdc++.h>
#include <queue>
#include <unordered_set>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);



/*
 * Complete the 'componentsInGraph' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts 2D_INTEGER_ARRAY gb as parameter.
 */
int explore(int node, unordered_set<int>& visited, unordered_map<int, vector<int>>& connections) {
    int count = 0;
    queue<int> q;
    q.push(node);
    visited.insert(node);
    
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        count++;
        
        for (int neighbor : connections[curr]) {
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
    return count;
}

vector<int> componentsInGraph(vector<vector<int>> gb) {
    unordered_map<int, vector<int>> connections;
    
    // Build adjacency list
    for (auto& edge : gb) {
        connections[edge[0]].push_back(edge[1]);
        connections[edge[1]].push_back(edge[0]);
    }
    
    int min_size = INT_MAX;
    int max_size = 0;
    unordered_set<int> visited; // Assuming node values are within 1-15000
    
    for (auto& [node, _] : connections) {
        if (!visited.count(node)) {
            int size = explore(node, visited, connections);
            if (size > 1) {
                min_size = min(min_size, size);
            }
            max_size = max(max_size, size);
        }
    }
    
    // Handle case where all components are size 1
    if (min_size == INT_MAX) min_size = 1;
    
    return {min_size, max_size};
}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> gb(n);

    for (int i = 0; i < n; i++) {
        gb[i].resize(2);

        string gb_row_temp_temp;
        getline(cin, gb_row_temp_temp);

        vector<string> gb_row_temp = split(rtrim(gb_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int gb_row_item = stoi(gb_row_temp[j]);

            gb[i][j] = gb_row_item;
        }
    }

    vector<int> result = componentsInGraph(gb);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << " ";
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
