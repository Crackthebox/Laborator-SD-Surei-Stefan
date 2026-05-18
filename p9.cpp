
#include <queue>
#include <vector>

using namespace std;

class MedianFinder {
private:
    priority_queue<int> jumatatea_inferioara;
    priority_queue<int, vector<int>, greater<int>> jumatatea_superioara;

public:
    MedianFinder() {
    }
    
    void addNum(int valoare_noua) {
        jumatatea_inferioara.push(valoare_noua);
        
        jumatatea_superioara.push(jumatatea_inferioara.top());
        jumatatea_inferioara.pop();
        
        if (jumatatea_superioara.size() > jumatatea_inferioara.size()) {
            jumatatea_inferioara.push(jumatatea_superioara.top());
            jumatatea_superioara.pop();
        }
    }
    
    double findMedian() {
        if (jumatatea_inferioara.size() > jumatatea_superioara.size()) {
            return jumatatea_inferioara.top();
        }
        return (jumatatea_inferioara.top() + jumatatea_superioara.top()) / 2.0;
    }
};