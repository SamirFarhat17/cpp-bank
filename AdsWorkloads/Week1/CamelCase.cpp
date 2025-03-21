#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

std::string split(std::string s) {
    std::string res = "";
    res += std::tolower(s[0]);
    for(int i = 1; i < s.length(); i++) {
        char c = s[i];
        if(c >= 'A' && c <= 'Z') {
            res += ' ';
            res += std::tolower(c);
        }
        else res += c;
    }
    return res;
}

std::string merge(std::string s, char type) {
    std::string res = "";
    if(type == 'C') res += std::toupper(s[0]);
    else res += s[0];
    
    for(int i = 1; i < s.length(); i++) {
        char c = s[i];
        if(c == ' ') {
            res += std::toupper(s[++i]);
        }
        else res += c;
    }
    if(type == 'M') {
        res += '(';
        res += ')';
    }
    
    return res;
}

std::string camelCase(std::string s) {
    
    char operation = s[0];
    char type = s[2];
    
    if(operation == 'S') return split(s.substr(4,s.size()));
    
    return merge(s.substr(4,s.size()), type);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    std::vector<std::string> lines;
    std::string line;
    
    while(std::getline(std::cin,line)) {
        if(line.empty()) break;
        lines.push_back(line);
    }
    
    for(std::string l : lines) std::cout << camelCase(l) << '\n';
    
    return 0;
}
