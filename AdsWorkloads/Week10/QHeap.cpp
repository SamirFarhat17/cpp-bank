#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

class Heap {
    
private:
    struct Comparator {
        bool operator()(const int& x, const int& y) {
            return x > y;
        }
    };
    std::stack<int> holder;
    std::priority_queue<int, vector<int>, Comparator> minPQ;
    
public:
    void insert(int x) {
        minPQ.push(x);
    }
    
    void del(int x) {
        while(minPQ.top() != x) {
            holder.push(minPQ.top());
            minPQ.pop();
        }
        minPQ.pop();
        while(!holder.empty()) {
            minPQ.push(holder.top());
            holder.pop();
        }
    }
    
    void print() {
        std::cout << minPQ.top() << '\n';
    }
};


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int queries;
    std::cin >> queries;
    std::cin.ignore();

    vector<string> lines;
    string line;
    while(std::getline(std::cin,line)) {
        lines.push_back(line);
        if(lines.size() == queries) break;
    }
    Heap heap;
    
    for(string l : lines) {
        //std::cout << l << '\n';
        char c = l[0];
        switch (c) {
            case '1' :
                heap.insert(std::stoi(l.substr(2)));
                break;
            case '2' :
                heap.del(std::stoi(l.substr(2)));
                break;
            case '3' :
                heap.print();
                break;
        }
    }
    
    return 0;
}
