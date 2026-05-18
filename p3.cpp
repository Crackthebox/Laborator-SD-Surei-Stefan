class Solution {
public:
    void recoverTree(TreeNode* root) {
        TreeNode* primul_gresit = nullptr;
        TreeNode* al_doilea_gresit = nullptr;
        TreeNode* nod_anterior = nullptr;
        TreeNode* nod_curent = root;

        while (nod_curent != nullptr) {
            if (nod_curent->left == nullptr) {
                if (nod_anterior != nullptr && nod_anterior->val > nod_curent->val) {
                    if (primul_gresit == nullptr) {
                        primul_gresit = nod_anterior;
                    }
                    al_doilea_gresit = nod_curent;
                }
                nod_anterior = nod_curent;
                nod_curent = nod_curent->right;
            } else {
                TreeNode* predecesor = nod_curent->left;
                while (predecesor->right != nullptr && predecesor->right != nod_curent) {
                    predecesor = predecesor->right;
                }

                if (predecesor->right == nullptr) {
                    predecesor->right = nod_curent;
                    nod_curent = nod_curent->left;
                } else {
                    predecesor->right = nullptr;
                    if (nod_anterior != nullptr && nod_anterior->val > nod_curent->val) {
                        if (primul_gresit == nullptr) {
                            primul_gresit = nod_anterior;
                        }
                        al_doilea_gresit = nod_curent;
                    }
                    nod_anterior = nod_curent;
                    nod_curent = nod_curent->right;
                }
            }
        }

        if (primul_gresit != nullptr && al_doilea_gresit != nullptr) {
            int valoare_temporara = primul_gresit->val;
            primul_gresit->val = al_doilea_gresit->val;
            al_doilea_gresit->val = valoare_temporara;
        }
    }
};