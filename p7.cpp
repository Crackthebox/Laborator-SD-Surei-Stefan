#include <iostream>
#include <vector>
#include <random>

using namespace std;

int main() {
    int n = 7;
    vector<int> a = {0, 1, 2, 0, 2, 1, 0};
    
    random_device rd;
    mt19937_64 rng(rd());
    
    vector<unsigned long long> H(n + 1);
    for (int i = 0; i <= n; ++i) {
        H[i] = rng();
    }
    
    vector<unsigned long long> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        unsigned long long val = (a[i] < n) ? H[a[i]] : H[n];
        pref[i + 1] = pref[i] ^ val;
    }
    
    vector<unsigned long long> tgt(n + 1, 0);
    tgt[0] = H[0];
    for (int i = 1; i <= n; ++i) {
        tgt[i] = tgt[i - 1] ^ H[i];
    }
    
    auto query = [&](int l, int r) {
        int len = r - l + 1;
        unsigned long long sub = pref[r + 1] ^ pref[l];
        return sub == tgt[len - 1];
    };
    
    cout << (query(0, 2) ? "Yes" : "No") << "\n";
    cout << (query(0, 3) ? "Yes" : "No") << "\n";
    cout << (query(3, 5) ? "Yes" : "No") << "\n";
    cout << (query(2, 4) ? "Yes" : "No") << "\n";
    cout << (query(6, 6) ? "Yes" : "No") << "\n";
    
    return 0;
}