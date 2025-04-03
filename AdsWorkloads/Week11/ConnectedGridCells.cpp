#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);



/*
 * Complete the 'connectedCell' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY matrix as parameter.
 */
int countRegionMembers(int r, int c, vector<vector<bool>>& visited, vector<vector<int>>& matrix,int& count) {
    visited[r][c] = true;
    count++;
    
    vector<vector<int>> dirs = {
        {-1,-1}, {-1,0}, {-1,1},
                {0,-1}, {0,1},
        {1,-1}, {1, 0}, {1,1}
    };
    
    for(vector<int> dir : dirs) {
        int newR = r + dir[0];
        int newC = c + dir[1];
        if(newR >= 0 && newC >= 0 && newR < matrix.size() && newC < matrix[0].size() 
            && matrix[newR][newC] == 1 && !visited[newR][newC]) {
            countRegionMembers(newR, newC, visited, matrix, count);
        }
    }
    
    
    return count;
}

int connectedCell(vector<vector<int>> matrix) {
    vector<vector<bool>> visited(matrix.size(), vector<bool>(matrix[0].size(),false));
    int largestRegion = 0;
    
    
    for(int row = 0; row < matrix.size(); row++) {
        for(int col = 0; col < matrix[0].size(); col++) {
            if(!visited[row][col] && matrix[row][col] == 1) {
                int currCount = 0;
                largestRegion = std::max(largestRegion, countRegionMembers(row, col, visited,matrix, currCount));
            }
        }
    }
    
    return largestRegion;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string m_temp;
    getline(cin, m_temp);

    int m = stoi(ltrim(rtrim(m_temp)));

    vector<vector<int>> matrix(n);

    for (int i = 0; i < n; i++) {
        matrix[i].resize(m);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < m; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    int result = connectedCell(matrix);

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
