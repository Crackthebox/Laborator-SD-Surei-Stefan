#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int elementCount, queryCount, inputValues[100001];
    long long int prefixSums[100001] = {0}, maxRangeSum = -100000001;

    cin >> elementCount;

    for (int i = 1; i <= elementCount; ++i) {
        cin >> inputValues[i];
        prefixSums[i] = prefixSums[i - 1] + inputValues[i];
    }

    cin >> queryCount;

    int leftBound, rightBound;
    for (int i = 1; i <= queryCount; ++i) {
        cin >> leftBound >> rightBound;

        if (leftBound > rightBound) {
            int temp = leftBound;
            leftBound = rightBound;
            rightBound = temp;
        }

        long long currentRangeSum = prefixSums[rightBound] - prefixSums[leftBound - 1];

        if (currentRangeSum > maxRangeSum) {
            maxRangeSum = currentRangeSum;
        }
    }

    cout << maxRangeSum;

    return 0;
}