#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

static std::unordered_map<int, std::vector<int>> groupings;

void merge(int g1, int g2) {
    groupings[g1].push_back(g2);
    groupings[g2].push_back(g1);
}

void printNetwork(int g, int n) {
    vector<bool> visited(n, false);
    std::queue<int> toVisit; 
    toVisit.push(g);
    int count = 1;
    visited[g] = true;
    
    while(!toVisit.empty()) {
        int size = toVisit.size();
        for(int i = 0; i < size; i++) {
            int node = toVisit.front();
            toVisit.pop();
            for(int n : groupings[node]) {
                if(!visited[n]) {
                    visited[n] = true;
                    toVisit.push(n);
                    count++;
                }
            }
        }
    }
    std::cout << count << '\n';
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */\
    std::string line;
    std::vector<std::string> lines;   
    while(std::getline(std::cin, line)) {
        lines.push_back(line);
    }
    
    int space = 0;
    
    for(char c : lines[0]) {
        if(c == ' ') break;
        space++;
    }
        
    int n = std::stoi(lines[0].substr(0,space));
    int q =  std::stoi(lines[0].substr(space+1));
    
    for(int i = 1; i < lines.size(); i++) {
        std::string instr = lines[i];
        if(instr[0] == 'M') {
            instr = instr.substr(2);
            int space = 0;
            for(char c : instr) {
                if(c == ' ') break;
                space++;
            }
            int g1 = std::stoi(instr.substr(0, space));
            int g2 =  std::stoi(instr.substr(space+1));
            merge(g1, g2);
        }
        else {
            printNetwork(std::stoi(instr.substr(2)), n);
        }
    }
    
    return 0;
}
