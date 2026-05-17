#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cassert>

using namespace std;

long long calculeaza_cel_mult(int k, const vector<int>& elemente_normalizate, int numar_valori_unice) {
    if (k == 0) return 0;
    
    vector<int> frecventa(numar_valori_unice + 1, 0);
    long long total_subsecvente = 0;
    int stanga = 0;
    int numar_distincte = 0;
    
    for (int dreapta = 0; dreapta < elemente_normalizate.size(); ++dreapta) {
        if (frecventa[elemente_normalizate[dreapta]] == 0) {
            numar_distincte++;
        }
        frecventa[elemente_normalizate[dreapta]]++;
        
        while (numar_distincte > k) {
            frecventa[elemente_normalizate[stanga]]--;
            if (frecventa[elemente_normalizate[stanga]] == 0) {
                numar_distincte--;
            }
            stanga++;
        }
        
        total_subsecvente += (dreapta - stanga + 1);
    }
    
    return total_subsecvente;
}

long long rezolva_secventa(int l, int u, const vector<unsigned int>& valori_initiale) {
    int n = valori_initiale.size();
    vector<unsigned int> valori_sortate = valori_initiale;
    
    sort(valori_sortate.begin(), valori_sortate.end());
    valori_sortate.erase(unique(valori_sortate.begin(), valori_sortate.end()), valori_sortate.end());
    
    vector<int> elemente_normalizate(n);
    for (int i = 0; i < n; ++i) {
        elemente_normalizate[i] = lower_bound(valori_sortate.begin(), valori_sortate.end(), valori_initiale[i]) - valori_sortate.begin();
    }
    
    int numar_valori_unice = valori_sortate.size();
    
    long long limita_superioara = calculeaza_cel_mult(u, elemente_normalizate, numar_valori_unice);
    long long limita_inferioara = calculeaza_cel_mult(l - 1, elemente_normalizate, numar_valori_unice);
    
    return limita_superioara - limita_inferioara;
}

int main() {
    vector<unsigned int> valori_test = {13, 13, 7, 9, 9};
    assert(rezolva_secventa(2, 3, valori_test) == 8);
    
    ifstream fin("secv5.in");
    ofstream fout("secv5.out");
    
    if (fin.is_open()) {
        int n, l, u;
        if (fin >> n >> l >> u) {
            vector<unsigned int> valori_initiale(n);
            for (int i = 0; i < n; ++i) {
                fin >> valori_initiale[i];
            }
            fout << rezolva_secventa(l, u, valori_initiale) << "\n";
        }
    } else {
        cout << "Testul intern pe exemplul din cerinta a trecut cu succes.\n";
        cout << "Pentru rezultatul pe fisiere, asigurati-va ca exista secv5.in in directorul curent.\n";
    }
    
    return 0;
}