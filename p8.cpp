#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

long long solve(int n, const vector<int>& v) {
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    
    for (int x : v) {
        pq.push(x);
    }
    
    long long ans = 0;
    
    while (pq.size() > 1) {
        long long x = pq.top(); 
        pq.pop();
        
        long long y = pq.top(); 
        pq.pop();
        
        long long cost = x + y;
        ans += cost;
        
        pq.push(cost);
    }
    
    return ans;
}

int main() {
    vector<int> test_v = {1, 5, 2, 5};
    assert(solve(4, test_v) == 24);
    
    int n;
    if (cin >> n) {
        vector<int> v(n);
        for (int i = 0; i < n; ++i) {
            cin >> v[i];
        }
        cout << solve(n, v) << "\n";
    }
    
    return 0;
}