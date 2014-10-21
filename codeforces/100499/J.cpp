#include <iostream>
#include <cstring>
using namespace std;

int n, m, k, a[111];
unsigned long long f[10001];

int main() {
    int nTest;
    cin >> nTest;
    while (nTest--) {
        cin >> n >> m >> k;
        for (int i = 0; i < n; i++) cin >> a[i];
        memset(f, 0, sizeof(f));
        f[0] = 1;
        int vMax = 0;
        for (int i = 0; i < n; i++) {
            for (int j = vMax; j >= 0; j--) {
                if (j + a[i] <= m) {
                    f[j + a[i]] += f[j];
                    vMax = max(vMax, j + a[i]);
                    if (f[j + a[i]] > k)
                        f[j + a[i]] = k;
                }
            }
        }
        if (f[m] >= k)
            cout << "ENOUGH" << endl;
        else
            cout << f[m] << endl;
    }
    return 0;
}
