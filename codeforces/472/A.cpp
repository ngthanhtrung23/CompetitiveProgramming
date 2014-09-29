#include <iostream>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        if (n % 2 == 0) cout << 4 << ' ' << n-4 << endl;
        else cout << 9 << ' ' << n-9 << endl;
    }
}
