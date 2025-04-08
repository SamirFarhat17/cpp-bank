#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'minimumMoves' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING_ARRAY grid
 *  2. INTEGER startX
 *  3. INTEGER startY
 *  4. INTEGER goalX
 *  5. INTEGER goalY
 */

int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) {
    int rows = grid.size();
    if (rows == 0) return -1;
    int cols = grid[0].size();
    
    pair<int, int> start = {startX, startY};
    pair<int, int> goal = {goalX, goalY};

    // Directions: up, down, left, right
    vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    // Visited matrix to track explored positions
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    
    // Queue for BFS: stores {row, col, moves}
    queue<tuple<int, int, int>> q;
    q.push({start.first, start.second, 0});
    visited[start.first][start.second] = true;

    while (!q.empty()) {
        auto [r, c, moves] = q.front();
        q.pop();

        // Check if current position is the goal
        if (r == goal.first && c == goal.second) {
            return moves;
        }

        // Explore all 4 directions
        for (auto [dr, dc] : dirs) {
            int newR = r, newC = c;

            // Slide until hitting a wall or boundary
            while (true) {
                int nextR = newR + dr;
                int nextC = newC + dc;

                // Check boundaries and obstacles
                if (nextR < 0 || nextR >= rows || nextC < 0 || nextC >= cols || grid[nextR][nextC] == 'X') {
                    break; // Stop sliding
                }
                newR = nextR;
                newC = nextC;
            }

            // If the landing position is unvisited, add to queue
            if (!visited[newR][newC]) {
                visited[newR][newC] = true;
                q.push({newR, newC, moves + 1});
            }
        }
    }

    return -1; // Goal unreachable
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int startX = stoi(first_multiple_input[0]);

    int startY = stoi(first_multiple_input[1]);

    int goalX = stoi(first_multiple_input[2]);

    int goalY = stoi(first_multiple_input[3]);

    int result = minimumMoves(grid, startX, startY, goalX, goalY);

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
