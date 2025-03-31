#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);



/*
 * Complete the 'truckTour' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY petrolpumps as parameter.
 */
bool doTraversal(vector<vector<int>>& petrolpumps, int idx) {
    int initial = idx;
    long gas = petrolpumps[idx][0];
    long distance = petrolpumps[idx][1];
    while(gas >= 0) {
        //make move
        gas -= distance;
        //increment idx
        if(idx == petrolpumps.size()-1) idx = 0;
        else idx++;
        //check
        if(gas < 0 ) return false;
        if(idx == initial) return true;
        
        //prepare for trip
        gas += petrolpumps[idx][0];
        distance = petrolpumps[idx][1]; 
    }
    
    return false;
    
}

int truckTourSlow(vector<vector<int>> petrolpumps) {
    for(int i = 0; i < petrolpumps.size(); i++) {
        if(doTraversal(petrolpumps, i)) return i;
    }
    
    return -1;
}

int truckTour(vector<vector<int>> petrolpumps) {
    int totalGas = 0, totalDistance = 0;
    int currGas = 0, startIdx = 0;

    for (int i = 0; i < petrolpumps.size(); i++) {
        totalGas += petrolpumps[i][0];
        totalDistance += petrolpumps[i][1];
        currGas += petrolpumps[i][0] - petrolpumps[i][1];

        // If at any point, currGas drops below zero, reset starting point
        if (currGas < 0) {
            startIdx = i + 1; // Move to the next station
            currGas = 0; // Reset gas balance
        }
    }

    return (totalGas >= totalDistance) ? startIdx : -1;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> petrolpumps(n);

    for (int i = 0; i < n; i++) {
        petrolpumps[i].resize(2);

        string petrolpumps_row_temp_temp;
        getline(cin, petrolpumps_row_temp_temp);

        vector<string> petrolpumps_row_temp = split(rtrim(petrolpumps_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int petrolpumps_row_item = stoi(petrolpumps_row_temp[j]);

            petrolpumps[i][j] = petrolpumps_row_item;
        }
    }

    int result = truckTour(petrolpumps);

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
