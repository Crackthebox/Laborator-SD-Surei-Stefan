#include <iostream>
#include <string>
#include <vector>

using namespace std;

string shortestString(const string& s) {
    vector<int> freq(256);
    for (char c : s) {
        freq[c]++;
    }
    
    string res = "";
    for (int i = 0; i < 256; i++) {
        if (freq[i] % 2 != 0) {
            res += (char)i;
        }
    }
    return res;
}

int main() {
    string s = "abacabaab";
    cout << shortestString(s) << "\n";
    return 0;
}