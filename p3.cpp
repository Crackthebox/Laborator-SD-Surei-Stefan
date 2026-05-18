#include <fstream>
#include <vector>

using namespace std;

const int MAX_BITS = 20; 
const int MAX_NODES = 2500000;

int trie[MAX_NODES][2];
int leaf_idx[MAX_NODES];
int nodes_count = 1;

void insert_trie(int val, int idx) {
    int node = 0;
    for (int i = MAX_BITS; i >= 0; --i) {
        int bit = (val >> i) & 1;
        if (trie[node][bit] == 0) {
            trie[node][bit] = nodes_count++;
        }
        node = trie[node][bit];
    }
    leaf_idx[node] = idx;
}

int query_trie(int val) {
    int node = 0;
    for (int i = MAX_BITS; i >= 0; --i) {
        int bit = (val >> i) & 1;
        int opp_bit = 1 - bit;
        
        if (trie[node][opp_bit] != 0) {
            node = trie[node][opp_bit];
        } else {
            node = trie[node][bit];
        }
    }
    return leaf_idx[node];
}

int main() {
    ifstream fin("xormax.in");
    ofstream fout("xormax.out");

    int n;
    if (!(fin >> n)) return 0;

    vector<int> P(n + 1, 0);
    insert_trie(0, 0);

    int max_xor = -1;
    int best_start = -1;
    int best_stop = -1;

    for (int i = 1; i <= n; ++i) {
        int x;
        fin >> x;
        P[i] = P[i - 1] ^ x;

        int best_prev_idx = query_trie(P[i]);
        int cand_xor = P[i] ^ P[best_prev_idx];

        if (cand_xor > max_xor) {
            max_xor = cand_xor;
            best_start = best_prev_idx + 1;
            best_stop = i;
        }

        insert_trie(P[i], i);
    }

    fout << max_xor << " " << best_start << " " << best_stop << "\n";

    return 0;
}