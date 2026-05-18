#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MAXN = 10005;
const int LOGN = 15;

string cuvinte[MAXN];
int p[MAXN];
int pos_in_sorted[MAXN];
int lcp[MAXN];
int rmq[MAXN][LOGN];
int lg2[MAXN];

int compute_lcp(const string& a, const string& b) {
    int i = 0;
    while (i < a.length() && i < b.length() && a[i] == b[i]) {
        i++;
    }
    return i;
}

int query_rmq(int L, int R) {
    int length = R - L + 1;
    int k = lg2[length];
    return min(rmq[L][k], rmq[R - (1 << k) + 1][k]);
}

int main() {
    ifstream fin("ratina.in");
    ofstream fout("ratina.out");

    int n, m;
    if (!(fin >> n >> m)) return 0;

    for (int i = 1; i <= n; ++i) {
        fin >> cuvinte[i];
        p[i] = i;
    }

    sort(p + 1, p + n + 1, [](int a, int b) {
        return cuvinte[a] < cuvinte[b];
    });

    for (int i = 1; i <= n; ++i) {
        pos_in_sorted[p[i]] = i;
    }

    for (int i = 1; i < n; ++i) {
        lcp[i] = compute_lcp(cuvinte[p[i]], cuvinte[p[i+1]]);
        rmq[i][0] = lcp[i];
    }

    lg2[1] = 0;
    for (int i = 2; i <= n; ++i) {
        lg2[i] = lg2[i / 2] + 1;
    }

    for (int j = 1; j < LOGN; ++j) {
        for (int i = 1; i + (1 << j) - 1 < n; ++i) {
            rmq[i][j] = min(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j - 1]);
        }
    }

    for (int i = 0; i < m; ++i) {
        int t;
        fin >> t;
        
        int min_p = n + 1, max_p = 0;
        int first_word_idx = -1;
        
        for (int j = 0; j < t; ++j) {
            int x;
            fin >> x;
            if (j == 0) first_word_idx = x;
            
            min_p = min(min_p, pos_in_sorted[x]);
            max_p = max(max_p, pos_in_sorted[x]);
        }

        if (min_p == max_p) {
            fout << cuvinte[first_word_idx].length() << "\n";
        } else {
            fout << query_rmq(min_p, max_p - 1) << "\n";
        }
    }

    return 0;
}