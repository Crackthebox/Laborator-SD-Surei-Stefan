#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class OpenHash {
private:
    enum State { E, O, D };

    struct Node {
        int val;
        State st;
        Node() : val(0), st(E) {}
    };

    vector<Node> H;
    int sz;
    int cap;

    int get_hash(int x) {
        return (x % cap + cap) % cap;
    }

    void resize() {
        int new_cap = cap * 2;
        vector<Node> new_H(new_cap);
        
        for (int i = 0; i < cap; ++i) {
            if (H[i].st == O) {
                int v = H[i].val;
                int n_idx = (v % new_cap + new_cap) % new_cap;
                
                while (new_H[n_idx].st == O) {
                    n_idx = (n_idx + 1) % new_cap;
                }
                
                new_H[n_idx].val = v;
                new_H[n_idx].st = O;
            }
        }
        
        H = move(new_H);
        cap = new_cap;
    }

public:
    OpenHash() {
        cap = 8;
        sz = 0;
        H.resize(cap);
    }

    void insert(int x) {
        if (exists(x)) return;

        if (sz + 1 > 0.5 * cap) {
            resize();
        }

        int idx = get_hash(x);
        while (H[idx].st == O) {
            idx = (idx + 1) % cap;
        }
        
        H[idx].val = x;
        H[idx].st = O;
        sz++;
    }

    bool exists(int x) {
        int idx = get_hash(x);
        int start = idx;

        while (H[idx].st != E) {
            if (H[idx].st == O && H[idx].val == x) {
                return true;
            }
            idx = (idx + 1) % cap;
            if (idx == start) break;
        }
        return false;
    }

    void erase(int x) {
        int idx = get_hash(x);
        int start = idx;

        while (H[idx].st != E) {
            if (H[idx].st == O && H[idx].val == x) {
                H[idx].st = D;
                sz--;
                return;
            }
            idx = (idx + 1) % cap;
            if (idx == start) break;
        }
    }
};

int main() {
    OpenHash ht;
    
    ht.insert(10);
    ht.insert(18); 
    ht.insert(26); 
    
    assert(ht.exists(18) == true);
    assert(ht.exists(10) == true);
    assert(ht.exists(99) == false);
    
    ht.erase(18);
    assert(ht.exists(18) == false);
    
    assert(ht.exists(26) == true);
    
    for(int i = 50; i < 65; i++) {
        ht.insert(i);
    }
    assert(ht.exists(60) == true);
    
    cout << "Toate testele pentru Open Addressing au trecut cu succes.\n";
    
    return 0;
}