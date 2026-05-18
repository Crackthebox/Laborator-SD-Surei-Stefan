#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    struct ComparareNoduri {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, ComparareNoduri> min_heap;
        
        for (ListNode* cap_lista : lists) {
            if (cap_lista != nullptr) {
                min_heap.push(cap_lista);
            }
        }
        
        ListNode cap_fals(0);
        ListNode* curent = &cap_fals;
        
        while (!min_heap.empty()) {
            ListNode* nod_minim = min_heap.top();
            min_heap.pop();
            
            curent->next = nod_minim;
            curent = curent->next;
            
            if (nod_minim->next != nullptr) {
                min_heap.push(nod_minim->next);
            }
        }
        
        return cap_fals.next;
    }
};

ListNode* creare_lista(const vector<int>& valori) {
    ListNode cap_fals(0);
    ListNode* curent = &cap_fals;
    for (int v : valori) {
        curent->next = new ListNode(v);
        curent = curent->next;
    }
    return cap_fals.next;
}

vector<int> extrage_valori(ListNode* cap) {
    vector<int> rezultat;
    while (cap != nullptr) {
        rezultat.push_back(cap->val);
        cap = cap->next;
    }
    return rezultat;
}

int main() {
    Solution solutie;
    
    ListNode* l1 = creare_lista({1, 4, 5});
    ListNode* l2 = creare_lista({1, 3, 4});
    ListNode* l3 = creare_lista({2, 6});
    vector<ListNode*> liste = {l1, l2, l3};
    
    ListNode* rezultat = solutie.mergeKLists(liste);
    vector<int> valori_rezultat = extrage_valori(rezultat);
    vector<int> valori_asteptate = {1, 1, 2, 3, 4, 4, 5, 6};
    
    assert(valori_rezultat == valori_asteptate);
    
    cout << "Testul principal a trecut cu succes.\n";
    
    return 0;
}