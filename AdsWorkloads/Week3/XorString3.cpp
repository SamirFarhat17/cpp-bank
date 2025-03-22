#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    std::vector<std::string> lines(2);
    std::string line;
    
    while(std::getline(std::cin,line)) {
        lines.push_back(line);
    }
    
    std::string s = lines[0];
    std::string t = lines[1];
    std::printf("s: %s \n t: %s", s, t);
    
    if(s.empty() || s.length() != t.length()) {
        std::cout << "\n";
        return 0;
    }
    
    for(int i = 0; i < s.length(); i++) {
        s[i] = (s[i] == t[i]) ? '0' : '1';
    }
    
    std::cout << s << std::endl;
     
    return 0;
}
