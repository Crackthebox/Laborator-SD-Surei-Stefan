#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

bool check(int L, const vector<string>& S) {
    if (L == 0) return true;
    for (const string& s : S) {
        if (s.length() < L) return false;
    }

    vector<unsigned long long> valid;
    unsigned long long mask = 0;
    unsigned long long limit = (1ULL << L) - 1;

    for (int i = 0; i < L; ++i) {
        mask = (mask << 1) | (S[0][i] - 'a');
    }
    valid.push_back(mask);
    
    for (size_t i = L; i < S[0].length(); ++i) {
        mask = ((mask << 1) & limit) | (S[0][i] - 'a');
        valid.push_back(mask);
    }
    
    sort(valid.begin(), valid.end());
    valid.erase(unique(valid.begin(), valid.end()), valid.end());

    for (size_t i = 1; i < S.size(); ++i) {
        vector<unsigned long long> curr;
        mask = 0;
        
        for (int j = 0; j < L; ++j) {
            mask = (mask << 1) | (S[i][j] - 'a');
        }
        curr.push_back(mask);
        
        for (size_t j = L; j < S[i].length(); ++j) {
            mask = ((mask << 1) & limit) | (S[i][j] - 'a');
            curr.push_back(mask);
        }
        
        sort(curr.begin(), curr.end());
        curr.erase(unique(curr.begin(), curr.end()), curr.end());

        vector<unsigned long long> next_v;
        set_intersection(valid.begin(), valid.end(), curr.begin(), curr.end(), back_inserter(next_v));
        valid = move(next_v);

        if (valid.empty()) return false;
    }
    return true;
}

int main() {
    ifstream fin("subsecvente2.in");
    ofstream fout("subsecvente2.out");

    int n;
    if (!(fin >> n)) return 0;

    vector<string> S(n);
    for (int i = 0; i < n; ++i) {
        fin >> S[i];
    }

    int low = 1, high = 60, ans = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid, S)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    fout << ans << "\n";
    return 0;
}