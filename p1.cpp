#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode {
    int value;
    int height;
    TreeNode* left_child;
    TreeNode* right_child;
    
    TreeNode(int node_value) : value(node_value), height(1), left_child(nullptr), right_child(nullptr) {}
};

class BalancedAVLTree {
private:
    TreeNode* tree_root;

    int get_node_height(TreeNode* current_node) {
        if (current_node == nullptr) {
            return 0;
        }
        return current_node->height;
    }

    int get_balance_factor(TreeNode* current_node) {
        if (current_node == nullptr) {
            return 0;
        }
        return get_node_height(current_node->right_child) - get_node_height(current_node->left_child);
    }

    void update_node_height(TreeNode* current_node) {
        if (current_node != nullptr) {
            int left_height = get_node_height(current_node->left_child);
            int right_height = get_node_height(current_node->right_child);
            current_node->height = 1 + max(left_height, right_height);
        }
    }

    TreeNode* rotate_right(TreeNode* unbalanced_node) {
        TreeNode* new_root = unbalanced_node->left_child;
        TreeNode* transfer_subtree = new_root->right_child;

        new_root->right_child = unbalanced_node;
        unbalanced_node->left_child = transfer_subtree;

        update_node_height(unbalanced_node);
        update_node_height(new_root);

        return new_root;
    }

    TreeNode* rotate_left(TreeNode* unbalanced_node) {
        TreeNode* new_root = unbalanced_node->right_child;
        TreeNode* transfer_subtree = new_root->left_child;

        new_root->left_child = unbalanced_node;
        unbalanced_node->right_child = transfer_subtree;

        update_node_height(unbalanced_node);
        update_node_height(new_root);

        return new_root;
    }

    TreeNode* balance_node(TreeNode* current_node) {
        update_node_height(current_node);
        
        int balance = get_balance_factor(current_node);

        if (balance == 2) {
            if (get_balance_factor(current_node->right_child) < 0) {
                current_node->right_child = rotate_right(current_node->right_child);
            }
            return rotate_left(current_node);
        }
        
        if (balance == -2) {
            if (get_balance_factor(current_node->left_child) > 0) {
                current_node->left_child = rotate_left(current_node->left_child);
            }
            return rotate_right(current_node);
        }
        
        return current_node;
    }

    TreeNode* insert_into_tree(TreeNode* current_node, int new_value) {
        if (current_node == nullptr) {
            return new TreeNode(new_value);
        }
        
        if (new_value < current_node->value) {
            current_node->left_child = insert_into_tree(current_node->left_child, new_value);
        } else if (new_value > current_node->value) {
            current_node->right_child = insert_into_tree(current_node->right_child, new_value);
        } else {
            return current_node;
        }
        
        return balance_node(current_node);
    }

    TreeNode* find_minimum_node(TreeNode* current_node) {
        if (current_node->left_child != nullptr) {
            return find_minimum_node(current_node->left_child);
        }
        return current_node;
    }

    TreeNode* remove_minimum_node(TreeNode* current_node) {
        if (current_node->left_child == nullptr) {
            return current_node->right_child;
        }
        current_node->left_child = remove_minimum_node(current_node->left_child);
        return balance_node(current_node);
    }

    TreeNode* delete_from_tree(TreeNode* current_node, int target_value) {
        if (current_node == nullptr) {
            return nullptr;
        }
        
        if (target_value < current_node->value) {
            current_node->left_child = delete_from_tree(current_node->left_child, target_value);
        } else if (target_value > current_node->value) {
            current_node->right_child = delete_from_tree(current_node->right_child, target_value);
        } else {
            TreeNode* left_branch = current_node->left_child;
            TreeNode* right_branch = current_node->right_child;
            
            delete current_node;
            
            if (right_branch == nullptr) {
                return left_branch;
            }
            
            TreeNode* minimum_in_right_branch = find_minimum_node(right_branch);
            minimum_in_right_branch->right_child = remove_minimum_node(right_branch);
            minimum_in_right_branch->left_child = left_branch;
            
            return balance_node(minimum_in_right_branch);
        }
        return balance_node(current_node);
    }

    bool search_tree(TreeNode* current_node, int target_value) {
        if (current_node == nullptr) {
            return false;
        }
        if (target_value == current_node->value) {
            return true;
        }
        if (target_value < current_node->value) {
            return search_tree(current_node->left_child, target_value);
        }
        return search_tree(current_node->right_child, target_value);
    }

    void destroy_tree(TreeNode* current_node) {
        if (current_node != nullptr) {
            destroy_tree(current_node->left_child);
            destroy_tree(current_node->right_child);
            delete current_node;
        }
    }

public:
    BalancedAVLTree() : tree_root(nullptr) {}

    ~BalancedAVLTree() {
        destroy_tree(tree_root);
    }

    void construct(const vector<int>& values) {
        for (int value : values) {
            insert(value);
        }
    }

    void insert(int value) {
        tree_root = insert_into_tree(tree_root, value);
    }

    void erase(int value) {
        tree_root = delete_from_tree(tree_root, value);
    }

    bool exists(int value) {
        return search_tree(tree_root, value);
    }

    int predecessor(int target_value) {
        TreeNode* iterator_node = tree_root;
        int best_predecessor = -2e9; 
        
        while (iterator_node != nullptr) {
            if (iterator_node->value < target_value) {
                best_predecessor = iterator_node->value;
                iterator_node = iterator_node->right_child;
            } else {
                iterator_node = iterator_node->left_child;
            }
        }
        return best_predecessor;
    }

    int successor(int target_value) {
        TreeNode* iterator_node = tree_root;
        int best_successor = 2e9; 
        
        while (iterator_node != nullptr) {
            if (iterator_node->value > target_value) {
                best_successor = iterator_node->value;
                iterator_node = iterator_node->left_child;
            } else {
                iterator_node = iterator_node->right_child;
            }
        }
        return best_successor;
    }
};

void run_tests() {
    BalancedAVLTree test_tree;
    
    vector<int> initial_values = {50, 30, 70, 20, 40, 60, 80};
    test_tree.construct(initial_values);
    
    if (test_tree.exists(40) && test_tree.exists(80) && !test_tree.exists(100)) {
        cout << "[PASS] Construct & Exists\n";
    } else {
        cout << "[FAIL] Construct & Exists\n";
    }
    
    test_tree.insert(35);
    test_tree.insert(65);
    
    if (test_tree.exists(35) && test_tree.exists(65)) {
        cout << "[PASS] Insert\n";
    } else {
        cout << "[FAIL] Insert\n";
    }
    
    if (test_tree.predecessor(40) == 35 && test_tree.predecessor(30) == 20) {
        cout << "[PASS] Predecessor\n";
    } else {
        cout << "[FAIL] Predecessor\n";
    }
    
    if (test_tree.successor(60) == 65 && test_tree.successor(70) == 80) {
        cout << "[PASS] Successor\n";
    } else {
        cout << "[FAIL] Successor\n";
    }
    
    test_tree.erase(30);
    test_tree.erase(70);
    
    if (!test_tree.exists(30) && !test_tree.exists(70) && test_tree.exists(35) && test_tree.exists(80)) {
        cout << "[PASS] Erase\n";
    } else {
        cout << "[FAIL] Erase\n";
    }
    
    if (test_tree.predecessor(35) == 20 && test_tree.successor(65) == 80) {
        cout << "[PASS] Tree structure maintained after deletion\n";
    } else {
        cout << "[FAIL] Tree structure maintained after deletion\n";
    }
}

int main() {
    run_tests();
    return 0;
}