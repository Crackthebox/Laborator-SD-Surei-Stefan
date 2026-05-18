#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
    ifstream fin("strabunica.in");
    ofstream fout("strabunica.out");

    int n;
    if (!(fin >> n)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        fin >> a[i];
    }

    stack<int> st;
    long long max_area = 0;

    for (int i = 0; i <= n; ++i) {
        long long h = (i == n) ? 0 : a[i];
        
        while (!st.empty() && h < a[st.top()]) {
            long long height = a[st.top()];
            st.pop();
            
            long long width = st.empty() ? i : i - st.top() - 1;
            max_area = max(max_area, height * width);
        }
        st.push(i);
    }

    fout << max_area << "\n";

    return 0;
}