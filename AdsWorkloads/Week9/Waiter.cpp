#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'waiter' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY number
 *  2. INTEGER q
 */
#include <iostream>
#include <vector>
#include <queue>

// Function to check if a number is prime
bool isPrime(int num, const std::vector<int>& primes) {
    for (int p : primes) {
        if (p * p > num) break;
        if (num % p == 0) return false;
    }
    return true;
}

// Function to generate the first 'q' prime numbers
std::vector<int> generatePrimes(int q) {
    std::vector<int> primes = {2};  // Start with the first prime
    int candidate = 3;
    
    while (primes.size() < q) {
        if (isPrime(candidate, primes)) {
            primes.push_back(candidate);
        }
        candidate += 2;  // Skip even numbers
    }
    return primes;
}

// Function to simulate the waiter's process
// Function to simulate the waiter's process
std::vector<int> waiter(std::vector<int> number, int q) {
    std::vector<int> answers;
    std::stack<int> A, B;
    std::vector<int> primes = generatePrimes(q);

    // Push numbers into A (keeping original order)
    for (int i = number.size() - 1; i >= 0; i--) {
        A.push(number[i]);
    }

    // Perform q iterations
    for (int i = 0; i < q; i++) {
        int prime = primes[i];

        // Filtering process
        std::stack<int> nextA;
        while (!A.empty()) {
            int num = A.top();
            A.pop();
            if (num % prime == 0) {
                B.push(num);
            } else {
                nextA.push(num);
            }
        }

        // Append B's contents to answers (from top to bottom)
        while (!B.empty()) {
            answers.push_back(B.top());
            B.pop();
        }

        // Move nextA back into A (to preserve order for next iteration)
        while (!nextA.empty()) {
            A.push(nextA.top());
            nextA.pop();
        }
    }

    // Append remaining elements of A to answers
    while (!A.empty()) {
        answers.push_back(A.top());
        A.pop();
    }

    return answers;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int q = stoi(first_multiple_input[1]);

    string number_temp_temp;
    getline(cin, number_temp_temp);

    vector<string> number_temp = split(rtrim(number_temp_temp));

    vector<int> number(n);

    for (int i = 0; i < n; i++) {
        int number_item = stoi(number_temp[i]);

        number[i] = number_item;
    }

    vector<int> result = waiter(number, q);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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
