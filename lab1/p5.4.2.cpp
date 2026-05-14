#include <iostream>

int integerSquareRoot(int n) {
    if (n == 0 || n == 1) return n;

    int left = 1, right = n;
    int result = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (mid <= n / mid) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

int main() {
    std::cout << "Sqrt of 10 is: " << integerSquareRoot(10) << "\n";
    std::cout << "Sqrt of 25 is: " << integerSquareRoot(25) << "\n";
    std::cout << "Sqrt of 2147395600 is: " << integerSquareRoot(2147395600) << "\n";
    
    return 0;
}