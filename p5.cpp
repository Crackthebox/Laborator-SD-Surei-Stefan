#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
int A[MAXN], P[MAXN], Q[MAXN];
int ans[MAXN];
int parent_set[MAXN];
vector<int> nodes[MAXN];
int root_trie[MAXN];
int max_comp[MAXN];
int global_max = 0;

int ch[3500005][2];
int node_cnt = 0;

int insert_trie(int val) {
    int r = ++node_cnt;
    int curr = r;
    for (int i = 29; i >= 0; --i) {
        int b = (val >> i) & 1;
        ch[curr][b] = ++node_cnt;
        curr = ch[curr][b];
    }
    return r;
}

int query_trie(int r, int val) {
    int curr = r;
    int res = 0;
    for (int i = 29; i >= 0; --i) {
        int b = (val >> i) & 1;
        if (ch[curr][b ^ 1]) {
            res |= (1 << i);
            curr = ch[curr][b ^ 1];
        } else {
            curr = ch[curr][b];
        }
    }
    return res;
}

int merge_trie(int u, int v) {
    if (!u || !v) return u ? u : v;
    ch[u][0] = merge_trie(ch[u][0], ch[v][0]);
    ch[u][1] = merge_trie(ch[u][1], ch[v][1]);
    return u;
}

int find_set(int v) {
    if (v == parent_set[v]) return v;
    return parent_set[v] = find_set(parent_set[v]);
}

void unite(int i) {
    int u = find_set(i - 1);
    int v = find_set(i);
    if (u == v) return;
    
    if (nodes[u].size() < nodes[v].size()) {
        swap(u, v);
    }
    
    for (int x : nodes[v]) {
        int mx = query_trie(root_trie[u], P[x]);
        if (mx > max_comp[u]) {
            max_comp[u] = mx;
        }
    }
    
    root_trie[u] = merge_trie(root_trie[u], root_trie[v]);
    
    for (int x : nodes[v]) {
        nodes[u].push_back(x);
    }
    
    if (max_comp[v] > max_comp[u]) {
        max_comp[u] = max_comp[v];
    }
    
    if (max_comp[u] > global_max) {
        global_max = max_comp[u];
    }
    
    parent_set[v] = u;
}

void run_test_example() {
    int n = 10;
    int test_A[] = {0, 169, 816, 709, 896, 58, 490, 97, 254, 99, 796};
    int test_Q[] = {0, 4, 2, 3, 10, 5, 6, 1, 8, 9, 7};
    
    global_max = 0;
    node_cnt = 0;
    
    P[0] = 0;
    for (int i = 1; i <= n; ++i) {
        A[i] = test_A[i];
        P[i] = P[i - 1] ^ A[i];
    }
    
    for (int i = 1; i <= n; ++i) {
        Q[i] = test_Q[i];
    }
    
    for (int i = 0; i <= n; ++i) {
        parent_set[i] = i;
        nodes[i].clear();
        nodes[i].push_back(i);
        root_trie[i] = insert_trie(P[i]);
        max_comp[i] = 0;
    }
    
    for (int i = n; i >= 1; --i) {
        unite(Q[i]);
        ans[i] = global_max;
    }
    
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) {
        run_test_example();
        return 0;
    }
    
    P[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> A[i];
        P[i] = P[i - 1] ^ A[i];
    }
    
    for (int i = 1; i <= n; ++i) {
        cin >> Q[i];
    }
    
    for (int i = 0; i <= n; ++i) {
        parent_set[i] = i;
        nodes[i].push_back(i);
        root_trie[i] = insert_trie(P[i]);
        max_comp[i] = 0;
    }
    
    for (int i = n; i >= 1; --i) {
        unite(Q[i]);
        ans[i] = global_max;
    }
    
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << "\n";
    }
    
    return 0;
}