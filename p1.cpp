#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    stack<int> st;
    for (int i = 1; i <= n; i++) {
        while (!st.empty() && a[st.top()] >= a[i]) {
            st.pop();
        }
        
        if (st.empty()) {
            cout << 0 << " ";
        } else {
            cout << st.top() << " ";
        }
        
        st.push(i);
    }
    cout << "\n";
    
    return 0;
}