class Solution {
private:
    bool valideaza_nod(TreeNode* nod_curent, TreeNode* limita_inferioara, TreeNode* limita_superioara) {
        if (nod_curent == nullptr) {
            return true;
        }
        
        if (limita_inferioara != nullptr && nod_curent->val <= limita_inferioara->val) {
            return false;
        }
        
        if (limita_superioara != nullptr && nod_curent->val >= limita_superioara->val) {
            return false;
        }
        
        bool este_stanga_valida = valideaza_nod(nod_curent->left, limita_inferioara, nod_curent);
        bool este_dreapta_valida = valideaza_nod(nod_curent->right, nod_curent, limita_superioara);
        
        return este_stanga_valida && este_dreapta_valida;
    }

public:
    bool isValidBST(TreeNode* root) {
        return valideaza_nod(root, nullptr, nullptr);
    }
};