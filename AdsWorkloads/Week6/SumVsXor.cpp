#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'sumXor' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts LONG_INTEGER n as parameter.
 */

int numZeroBits(long n) {
    int bitRep =0;
    long curr = 1;
    if(n == 1 || n == 0) bitRep = 1;
    
    while(n > curr) {
        curr <<= 1;
        bitRep++;
    }
    
    int count = 0;
    for(int i = 0; i < bitRep; i++) {
        if((n & ( 1L << i)) == 0) count++;
    }
    
    return count;
}

long sumXor(long n) {
    if(n == 0 || n == 1) return 1;
    
    /*for(int i = 0; i <= n; i++) {
        if((n ^ i) == (n + i)) counter++;
    }*/
    
    return std::pow(2,numZeroBits(n));
    //return counter;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    long n = stol(ltrim(rtrim(n_temp)));

    long result = sumXor(n);

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
