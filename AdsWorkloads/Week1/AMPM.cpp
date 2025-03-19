#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string timeConversion(string s) {
    if(s.empty()) return "";
    
    int  mtHour = std::stoi(s.substr(0,2));
    bool afterNoon = s[s.length()-2] == 'P';
    if(afterNoon && mtHour != 12) mtHour +=12;
    else if(!afterNoon && mtHour == 12) mtHour = 0;
    std::string strMtHour = std::to_string(mtHour);
    
    if(mtHour > 10) {
        s[0] = strMtHour[0];
        s[1] = strMtHour[1];
    }
    else {
        s[0] = '0';
        s[1] = strMtHour[0];
    }
    s.resize(s.size() - 2);
    
    return s;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = timeConversion(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
