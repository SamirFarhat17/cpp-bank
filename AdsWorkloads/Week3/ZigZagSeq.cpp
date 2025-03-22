#include <bits/stdc++.h>
using namespace std;

void findZigZagSequence(vector <int> a, int n){
    int k = (n+1)/2;
    std::priority_queue<int> decreasing;
    std::priority_queue<int, std::vector<int>, greater<int>> increasing;
    
    for(int num : a) {
        decreasing.push(num);
        increasing.push(num);
    }
    
    for(int i = 0; i < k; i++) {
        std::cout << increasing.top() << ' ';
        increasing.pop();
    }
    for(int i = k; i < n; i++) {
        std::cout << decreasing.top() << ' ';
        decreasing.pop();
    }
    std::cout << '\n';
}

int main() {
    int n, x;
    int test_cases;
    cin >> test_cases;

    for(int cs = 1; cs <= test_cases; cs++){
        cin >> n;
        vector < int > a;
        for(int i = 0; i < n; i++){
            cin >> x;
            a.push_back(x);
        }
        findZigZagSequence(a, n);
    }
}
