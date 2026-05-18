#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>

using namespace std;

void quickSelect(vector<int>& v, int left, int right, int k) {
    if (left >= right) return;

    int i = left, j = right;
    int pivot = v[left + rand() % (right - left + 1)];

    while (i <= j) {
        while (v[i] < pivot) i++;
        while (v[j] > pivot) j--;
        if (i <= j) {
            swap(v[i], v[j]);
            i++;
            j--;
        }
    }

    if (left < j && k <= j) quickSelect(v, left, j, k);
    if (i < right && k >= i) quickSelect(v, i, right, k);
}

int main() {
    ifstream fin("sdo.in");
    ofstream fout("sdo.out");

    

    int n, k;
    if (!(fin >> n >> k)) return 0;

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        fin >> v[i];
    }

    srand(time(NULL));
    quickSelect(v, 0, n - 1, k - 1);

    fout << v[k - 1] << "\n";

    return 0;
}