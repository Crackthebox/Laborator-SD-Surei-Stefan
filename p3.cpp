#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
    ifstream fin("fadema.in");
    ofstream fout("fadema.out");

    int n, m;
    if (!(fin >> n >> m)) return 0;

    vector<vector<int>> mat(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fin >> mat[i][j];
        }
    }

    vector<int> h(m, 0);
    int max_area = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == 0 || mat[i][j] == mat[i - 1][j]) {
                h[j] = 1;
            } else {
                h[j]++;
            }
        }

        int j = 0;
        while (j < m) {
            int k = j;
            while (k + 1 < m && mat[i][k] != mat[i][k + 1]) {
                k++;
            }

            stack<int> st;
            for (int x = j; x <= k + 1; ++x) {
                int current_h = (x <= k) ? h[x] : 0;
                while (!st.empty() && current_h < h[st.top()]) {
                    int height = h[st.top()];
                    st.pop();
                    int width = st.empty() ? (x - j) : (x - st.top() - 1);
                    max_area = max(max_area, height * width);
                }
                st.push(x);
            }
            j = k + 1;
        }
    }

    fout << max_area << "\n";
    return 0;
}