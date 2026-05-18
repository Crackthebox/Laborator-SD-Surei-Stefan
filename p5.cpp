#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>

using namespace std;

class MaxHeap {
private:
    vector<int> elemente_arbore;

    int obtine_index_parinte(int index_curent) {
        return (index_curent - 1) / 2;
    }

    int obtine_index_copil_stang(int index_curent) {
        return 2 * index_curent + 1;
    }

    int obtine_index_copil_drept(int index_curent) {
        return 2 * index_curent + 2;
    }

    void urca_nodul(int index_curent) {
        while (index_curent > 0 && elemente_arbore[index_curent] > elemente_arbore[obtine_index_parinte(index_curent)]) {
            swap(elemente_arbore[index_curent], elemente_arbore[obtine_index_parinte(index_curent)]);
            index_curent = obtine_index_parinte(index_curent);
        }
    }

    void coboara_nodul(int index_curent) {
        int index_maxim = index_curent;
        int copil_stang = obtine_index_copil_stang(index_curent);
        int copil_drept = obtine_index_copil_drept(index_curent);
        int numar_total_elemente = elemente_arbore.size();

        if (copil_stang < numar_total_elemente && elemente_arbore[copil_stang] > elemente_arbore[index_maxim]) {
            index_maxim = copil_stang;
        }

        if (copil_drept < numar_total_elemente && elemente_arbore[copil_drept] > elemente_arbore[index_maxim]) {
            index_maxim = copil_drept;
        }

        if (index_maxim != index_curent) {
            swap(elemente_arbore[index_curent], elemente_arbore[index_maxim]);
            coboara_nodul(index_maxim);
        }
    }

public:
    void insert(int valoare_noua) {
        elemente_arbore.push_back(valoare_noua);
        urca_nodul(elemente_arbore.size() - 1);
    }

    int top() {
        if (elemente_arbore.empty()) {
            throw out_of_range("Nu se poate citi din heap: structura este goala.");
        }
        return elemente_arbore[0];
    }

    void pop() {
        if (elemente_arbore.empty()) {
            throw out_of_range("Nu se poate sterge din heap: structura este goala.");
        }
        
        elemente_arbore[0] = elemente_arbore.back();
        elemente_arbore.pop_back();
        
        if (!elemente_arbore.empty()) {
            coboara_nodul(0);
        }
    }
};

int main() {
    MaxHeap coada_prioritati;
    
    coada_prioritati.insert(15);
    coada_prioritati.insert(40);
    coada_prioritati.insert(25);
    coada_prioritati.insert(50);
    coada_prioritati.insert(30);
    
    assert(coada_prioritati.top() == 50);
    
    coada_prioritati.pop();
    assert(coada_prioritati.top() == 40);
    
    coada_prioritati.pop();
    assert(coada_prioritati.top() == 30);
    
    coada_prioritati.pop();
    assert(coada_prioritati.top() == 25);
    
    coada_prioritati.insert(100);
    assert(coada_prioritati.top() == 100);
    
    cout << "Toate testele pentru MaxHeap au trecut cu succes.\n";
    
    return 0;
}