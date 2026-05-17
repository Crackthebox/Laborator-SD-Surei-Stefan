#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>

using namespace std;

class ChainingHash {
private:
    vector<list<int>> H;
    int sz;
    int cap;

    int get_hash(int x) {
        return (x % cap + cap) % cap;
    }

    void resize() {
        int new_cap = cap * 2;
        vector<list<int>> new_H(new_cap);
        
        for (int i = 0; i < cap; ++i) {
            for (int x : H[i]) {
                int n_idx = (x % new_cap + new_cap) % new_cap;
                new_H[n_idx].push_back(x);
            }
        }
        
        H = move(new_H);
        cap = new_cap;
    }

public:
    ChainingHash() {
        cap = 8;
        sz = 0;
        H.resize(cap);
    }

    void insert(int x) {
        if (exists(x)) return;

        if (sz + 1 > 0.75 * cap) {
            resize();
        }

        int idx = get_hash(x);
        H[idx].push_back(x);
        sz++;
    }

    bool exists(int x) {
        int idx = get_hash(x);
        for (int v : H[idx]) {
            if (v == x) return true;
        }
        return false;
    }

    void erase(int x) {
        int idx = get_hash(x);
        auto it = find(H[idx].begin(), H[idx].end(), x);
        
        if (it != H[idx].end()) {
            H[idx].erase(it);
            sz--;
        }
    }
};

int main() {
    ChainingHash ht;
    
    ht.insert(5);
    ht.insert(13);
    ht.insert(21);
    
    assert(ht.exists(5) == true);
    assert(ht.exists(13) == true);
    assert(ht.exists(100) == false);
    
    ht.erase(13);
    assert(ht.exists(13) == false);
    assert(ht.exists(5) == true);
    
    for(int i = 100; i < 120; i++) {
        ht.insert(i);
    }
    assert(ht.exists(115) == true);
    assert(ht.exists(5) == true);
    
    cout << "Toate testele pentru Chaining au trecut cu succes.\n";
    
    return 0;
}