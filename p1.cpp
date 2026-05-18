#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct TrieNode {
    int cnt;
    int desc;
    TrieNode* fii[26];

    TrieNode() {
        cnt = 0;
        desc = 0;
        for (int i = 0; i < 26; ++i) {
            fii[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* radacina;

    void elibereaza_memorie(TrieNode* nod) {
        if (!nod) return;
        for (int i = 0; i < 26; ++i) {
            if (nod->fii[i] != nullptr) {
                elibereaza_memorie(nod->fii[i]);
            }
        }
        delete nod;
    }

public:
    Trie() {
        radacina = new TrieNode();
    }

    ~Trie() {
        elibereaza_memorie(radacina);
    }

    void insereaza(const string& cuvant) {
        TrieNode* curent = radacina;
        for (char c : cuvant) {
            int litera = c - 'a';
            if (curent->fii[litera] == nullptr) {
                curent->fii[litera] = new TrieNode();
            }
            curent = curent->fii[litera];
            curent->desc++;
        }
        curent->cnt++;
    }

    void sterge(const string& cuvant) {
        TrieNode* curent = radacina;
        TrieNode* parinti[25]; 
        
        for (int i = 0; i < cuvant.length(); ++i) {
            parinti[i] = curent;
            curent = curent->fii[cuvant[i] - 'a'];
        }
        curent->cnt--;
        
        for (int i = cuvant.length() - 1; i >= 0; --i) {
            TrieNode* nod = parinti[i]->fii[cuvant[i] - 'a'];
            nod->desc--;
            
            if (nod->desc == 0 && nod->cnt == 0) {
                delete nod;
                parinti[i]->fii[cuvant[i] - 'a'] = nullptr;
            }
        }
    }

    int numara(const string& cuvant) {
        TrieNode* curent = radacina;
        for (char c : cuvant) {
            int litera = c - 'a';
            if (curent->fii[litera] == nullptr) {
                return 0;
            }
            curent = curent->fii[litera];
        }
        return curent->cnt;
    }

    int prefix_comun_maxim(const string& cuvant) {
        TrieNode* curent = radacina;
        int lungime = 0;
        for (char c : cuvant) {
            int litera = c - 'a';
            if (curent->fii[litera] == nullptr) {
                break;
            }
            curent = curent->fii[litera];
            lungime++;
        }
        return lungime;
    }
};

int main() {
    ifstream fin("trie.in");
    ofstream fout("trie.out");

    int tip_operatie;
    string cuvant;
    Trie arbore_prefixe;

    while (fin >> tip_operatie >> cuvant) {
        if (tip_operatie == 0) {
            arbore_prefixe.insereaza(cuvant);
        } else if (tip_operatie == 1) {
            arbore_prefixe.sterge(cuvant);
        } else if (tip_operatie == 2) {
            fout << arbore_prefixe.numara(cuvant) << "\n";
        } else if (tip_operatie == 3) {
            fout << arbore_prefixe.prefix_comun_maxim(cuvant) << "\n";
        }
    }

    return 0;
}