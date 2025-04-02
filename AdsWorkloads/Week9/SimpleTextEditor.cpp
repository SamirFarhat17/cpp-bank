#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int ops;
    std::cin >> ops;
    std::cin.ignore();
    
    std::vector<std::string> lines;
    std::string line;
    
    while(std::getline(std::cin, line)) {
        lines.push_back(line);
        if(lines.size() == ops) break;
    }
    
    std::stack<std::string> saveState;
    saveState.push("");
    std::string s = "";
    
    for(std::string l : lines) {
        char c = l[0];
        switch(c) {
            case '1': 
                saveState.push(s);
                s += l.substr(2);
                break;
            case '2': 
                saveState.push(s);
                s.resize(s.length() - std::stoi(l.substr(2)));
                break;
            case '3':
                std::cout << s[std::stoi(l.substr(2))-1] << '\n';
                break;
            case '4': 
                s = saveState.top();
                saveState.pop();
                break;
        }
        //std::cout << s << '\n';
    }
    
    return 0;
}
