#include <string>
#include <cstring>
#include <climits>

using namespace std;

class Codec {
private:
    void parcurge_preordine(TreeNode* nod_curent, string& text_codat) {
        if (nod_curent == nullptr) {
            return;
        }
        
        char buffer_memorie[4];
        memcpy(buffer_memorie, &(nod_curent->val), 4);
        text_codat.append(buffer_memorie, 4);
        
        parcurge_preordine(nod_curent->left, text_codat);
        parcurge_preordine(nod_curent->right, text_codat);
    }

    TreeNode* reconstruieste_arbore(const string& text_codat, int& pozitie_citire, int limita_inferioara, int limita_superioara) {
        if (pozitie_citire >= text_codat.size()) {
            return nullptr;
        }
        
        int valoare_curenta;
        memcpy(&valoare_curenta, text_codat.data() + pozitie_citire, 4);
        
        if (valoare_curenta < limita_inferioara || valoare_curenta > limita_superioara) {
            return nullptr;
        }
        
        pozitie_citire += 4;
        TreeNode* nod_nou = new TreeNode(valoare_curenta);
        
        nod_nou->left = reconstruieste_arbore(text_codat, pozitie_citire, limita_inferioara, valoare_curenta);
        nod_nou->right = reconstruieste_arbore(text_codat, pozitie_citire, valoare_curenta, limita_superioara);
        
        return nod_nou;
    }

public:
    string serialize(TreeNode* root) {
        string rezultat_codare = "";
        parcurge_preordine(root, rezultat_codare);
        return rezultat_codare;
    }

    TreeNode* deserialize(string data) {
        int pozitie_initiala = 0;
        return reconstruieste_arbore(data, pozitie_initiala, INT_MIN, INT_MAX);
    }
};