#include <iostream>
#include <vector>

using namespace std;

bool knows(int i, int j, const vector<vector<int>>& mat) {
    return mat[i][j] == 1;
}

int findCelebrity(int n, const vector<vector<int>>& mat) {
    int candidate = 0;
    
    for (int i = 1; i < n; i++) {
        if (knows(candidate, i, mat)) {
            candidate = i;
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (i != candidate) {
            if (knows(candidate, i, mat) || !knows(i, candidate, mat)) {
                return -1;
            }
        }
    }
    return candidate;
}

int main() {
    vector<vector<int>> matrix = {
        {0, 1, 0},
        {0, 0, 0},
        {0, 1, 0}
    };
    cout << findCelebrity(3, matrix) << "\n";
    return 0;
}