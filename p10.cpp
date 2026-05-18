#include <fstream>
#include <deque>

using namespace std;

int main() {
    ifstream fin("deque.in");
    ofstream fout("deque.out");

    int numar_elemente, lungime_fereastra;
    if (!(fin >> numar_elemente >> lungime_fereastra)) return 0;

    long long suma_minime = 0;
    deque<pair<int, int>> coada_minime;

    for (int index_curent = 0; index_curent < numar_elemente; ++index_curent) {
        int valoare_curenta;
        fin >> valoare_curenta;

        while (!coada_minime.empty() && coada_minime.back().first >= valoare_curenta) {
            coada_minime.pop_back();
        }

        coada_minime.push_back({valoare_curenta, index_curent});

        if (coada_minime.front().second <= index_curent - lungime_fereastra) {
            coada_minime.pop_front();
        }

        if (index_curent >= lungime_fereastra - 1) {
            suma_minime += coada_minime.front().first;
        }
    }

    fout << suma_minime << "\n";

    return 0;
}