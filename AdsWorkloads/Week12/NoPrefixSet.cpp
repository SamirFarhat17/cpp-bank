#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'noPrefix' function below.
 *
 * The function accepts STRING_ARRAY words as parameter.
 */
class NoPrefixTrie {
private:
    NoPrefixTrie* tries[26]{nullptr};
    bool isEnd;
public:
    NoPrefixTrie() : isEnd(false) {};
    
    ~NoPrefixTrie() {
        for(NoPrefixTrie* t : tries) delete t;
    }
    
    bool insert(std::string word) {
        NoPrefixTrie* curr = this;
        for(char c : word) {
            if(curr->tries[c - 'a'] == nullptr) {
                curr->tries[c - 'a'] = new NoPrefixTrie();
            }
            curr = curr->tries[c - 'a'];
            if(curr->isEnd) return false;
            
        }
        curr->isEnd = true;
        for(int i = 0; i < 26; i++) {
            if(curr->tries[i] != nullptr) return false;
        }
        
        return true;
    }
};

void noPrefix(vector<string> words) {
    NoPrefixTrie npt;
    for(std::string word : words) {
        if(!npt.insert(word)) {
            std::cout << "BAD SET\n" << word << '\n';
            return;
        }
    }
    std::cout << "GOOD SET\n";
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> words(n);

    for (int i = 0; i < n; i++) {
        string words_item;
        getline(cin, words_item);

        words[i] = words_item;
    }

    noPrefix(words);

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
