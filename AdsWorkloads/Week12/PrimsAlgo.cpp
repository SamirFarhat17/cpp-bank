#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'prims' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY edges
 *  3. INTEGER start
 */
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>
using namespace std;

typedef pair<int, int> pii; // (weight, node)

int prims(int n, vector<vector<int>> edges, int start) {
    int totalWeight = 0;
    
    // Create proper adjacency list (each node maps to a list of neighbors)
    unordered_map<int, vector<pii>> adj;
    for(auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        adj[u].emplace_back(w, v); // weight first for priority_queue
        adj[v].emplace_back(w, u); // undirected graph
    }
    
    vector<int> key(n+1, INT_MAX);
    vector<bool> visited(n+1, false);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    
    pq.push({0, start});
    key[start] = 0;
    
    while(!pq.empty()) {
        int u = pq.top().second;
        int weight = pq.top().first;
        pq.pop();
        
        if(visited[u]) continue;
        
        visited[u] = true;
        totalWeight += weight;
        
        for(auto& neighbor : adj[u]) {
            int v = neighbor.second;
            int w = neighbor.first;
            
            if(!visited[v] && w < key[v]) {
                key[v] = w;
                pq.push({key[v], v});
            }
        }
    }
    
    return totalWeight;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    vector<vector<int>> edges(m);

    for (int i = 0; i < m; i++) {
        edges[i].resize(3);

        string edges_row_temp_temp;
        getline(cin, edges_row_temp_temp);

        vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

        for (int j = 0; j < 3; j++) {
            int edges_row_item = stoi(edges_row_temp[j]);

            edges[i][j] = edges_row_item;
        }
    }

    string start_temp;
    getline(cin, start_temp);

    int start = stoi(ltrim(rtrim(start_temp)));

    int result = prims(n, edges, start);

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
