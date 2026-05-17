#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

unsigned long long poly_hash(const string& s) {
    const unsigned long long B = 131;
    unsigned long long h = 0;
    
    for (char c : s) {
        h = h * B + c;
    }
    
    return h;
}

int main() {
    string s1 = "algoritm";
    string s2 = "programare";
    string s3 = "algoritm";
    
    unsigned long long h1 = poly_hash(s1);
    unsigned long long h2 = poly_hash(s2);
    unsigned long long h3 = poly_hash(s3);
    
    assert(h1 == h3);
    assert(h1 != h2);
    
    string s4 = "a";
    string s5 = "b";
    assert(poly_hash(s4) != poly_hash(s5));
    
    cout << "Toate testele pentru String Hashing au trecut cu succes.\n";
    
    return 0;
}