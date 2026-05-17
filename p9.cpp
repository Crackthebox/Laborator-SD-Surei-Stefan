#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    int capacitate_a, capacitate_b, volum_dorit;
    if (!(cin >> capacitate_a >> capacitate_b >> volum_dorit)) return 0;

    int total_stari = (capacitate_a + 1) * (capacitate_b + 1);
    vector<int> stare_parinte(total_stari, -1);
    vector<int> operatie_parinte(total_stari, 0);

    queue<int> coada_stari;
    
    int stare_initiala = 0;
    coada_stari.push(stare_initiala);
    stare_parinte[stare_initiala] = -2; 

    int stare_finala = -1;

    while (!coada_stari.empty()) {
        int stare_curenta = coada_stari.front();
        coada_stari.pop();

        int volum_a = stare_curenta / (capacitate_b + 1);
        int volum_b = stare_curenta % (capacitate_b + 1);

        if (volum_a == volum_dorit || volum_b == volum_dorit) {
            stare_finala = stare_curenta;
            break;
        }

        auto adauga_stare = [&](int urmatorul_a, int urmatorul_b, int tip_operatie) {
            int urmatoarea_stare = urmatorul_a * (capacitate_b + 1) + urmatorul_b;
            if (stare_parinte[urmatoarea_stare] == -1) {
                stare_parinte[urmatoarea_stare] = stare_curenta;
                operatie_parinte[urmatoarea_stare] = tip_operatie;
                coada_stari.push(urmatoarea_stare);
            }
        };

        adauga_stare(capacitate_a, volum_b, 1);
        adauga_stare(volum_a, capacitate_b, 2);

        adauga_stare(0, volum_b, 3);
        adauga_stare(volum_a, 0, 4);

        int transfer_ab = min(volum_a, capacitate_b - volum_b);
        adauga_stare(volum_a - transfer_ab, volum_b + transfer_ab, 5);

        int transfer_ba = min(volum_b, capacitate_a - volum_a);
        adauga_stare(volum_a + transfer_ba, volum_b - transfer_ba, 6);
    }

    if (stare_finala != -1) {
        vector<int> istoric_operatii;
        int stare_urmarire = stare_finala;

        while (stare_urmarire != 0) {
            istoric_operatii.push_back(operatie_parinte[stare_urmarire]);
            stare_urmarire = stare_parinte[stare_urmarire];
        }

        reverse(istoric_operatii.begin(), istoric_operatii.end());

        string nume_operatii[] = {"", "R A", "R B", "A C", "B C", "A B", "B A"};
        
        cout << istoric_operatii.size() << "\n";
        for (int operatie : istoric_operatii) {
            cout << nume_operatii[operatie] << "\n";
        }
    }

    return 0;
}