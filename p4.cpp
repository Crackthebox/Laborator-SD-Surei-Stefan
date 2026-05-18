#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct SearchResult {
    int id;
    int freq;

    bool operator<(const SearchResult& other) const {
        if (freq != other.freq) {
            return freq > other.freq;
        }
        return id < other.id;
    }
};

struct TrieNode {
    TrieNode* children[26];
    vector<SearchResult> top_k;
    
    TrieNode() {
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Q, K;
    if (!(cin >> Q >> K)) return 0;

    TrieNode* root = new TrieNode();
    vector<TrieNode*> nav_stack;
    nav_stack.push_back(root);
    
    string current_typed = "";

    map<string, int> word_to_id;
    vector<string> id_to_word;
    vector<int> freq;
    int next_id = 0;

    for (int query_idx = 0; query_idx < Q; ++query_idx) {
        int type;
        cin >> type;

        if (type == 1) {
            char c;
            cin >> c;
            current_typed += c;

            TrieNode* current_node = nav_stack.back();
            
            if (current_node == nullptr || current_node->children[c - 'a'] == nullptr) {
                nav_stack.push_back(nullptr);
                cout << -1 << "\n";
            } else {
                current_node = current_node->children[c - 'a'];
                nav_stack.push_back(current_node);

                if (current_node->top_k.empty()) {
                    cout << -1 << "\n";
                } else {
                    for (int i = 0; i < current_node->top_k.size(); ++i) {
                        cout << current_node->top_k[i].id << (i == current_node->top_k.size() - 1 ? "" : " ");
                    }
                    cout << "\n";
                }
            }
        } 
        else if (type == 2) {
            current_typed = "";
            nav_stack.clear();
            nav_stack.push_back(root);
        } 
        else if (type == 3) {
            if (current_typed.length() > 0) {
                current_typed.pop_back();
                nav_stack.pop_back();
            }
        } 
        else if (type == 4) {
            if (current_typed.empty()) continue;

            int id;
            if (word_to_id.find(current_typed) == word_to_id.end()) {
                id = query_idx;
                word_to_id[current_typed] = id;
                id_to_word.push_back(current_typed);
                freq.push_back(1);
            } else {
                id = word_to_id[current_typed];
                int idx_in_arrays = distance(id_to_word.begin(), find(id_to_word.begin(), id_to_word.end(), current_typed));
                freq[idx_in_arrays]++;
            }

            int curr_freq = freq[distance(id_to_word.begin(), find(id_to_word.begin(), id_to_word.end(), current_typed))];

            TrieNode* curr = root;
            for (char c : current_typed) {
                if (curr->children[c - 'a'] == nullptr) {
                    curr->children[c - 'a'] = new TrieNode();
                }
                curr = curr->children[c - 'a'];

                bool found_in_top = false;
                for (auto& item : curr->top_k) {
                    if (item.id == id) {
                        item.freq = curr_freq;
                        found_in_top = true;
                        break;
                    }
                }

                if (!found_in_top) {
                    curr->top_k.push_back({id, curr_freq});
                }

                sort(curr->top_k.begin(), curr->top_k.end());

                if (curr->top_k.size() > K) {
                    curr->top_k.pop_back();
                }
            }
            
            TrieNode* rebuild_node = root;
            nav_stack.clear();
            nav_stack.push_back(root);
            bool dead_end = false;
            
            for(char c : current_typed) {
                if(!dead_end && rebuild_node->children[c - 'a'] != nullptr) {
                    rebuild_node = rebuild_node->children[c - 'a'];
                    nav_stack.push_back(rebuild_node);
                } else {
                    dead_end = true;
                    nav_stack.push_back(nullptr);
                }
            }
        }
    }

    return 0;
}