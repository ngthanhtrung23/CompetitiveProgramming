#include <iostream>
#include <algorithm>
using namespace std;

int a[2011];

int main() {
    int n, k;
    while (cin >> n >> k) {
        for(int i = 1; i <= n; ++i) cin >> a[i];
        sort(a+1, a+n+1);
        int res = 0;
        for(int i = n; i > 0; i -= k)
            res += a[i] * 2 - 2;
        cout << res << endl;
    }
}
