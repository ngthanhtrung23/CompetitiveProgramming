#include <bits/stdc++.h>

using namespace std;

int main() {
#ifdef LDT
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //1 2 3 4 5 .. n -> 1
    //1 n 2 (n-1) ... -> n - 1
    int n, k;
    cin >> n >> k;
    //1 2 3 .... x - 1|x n  
    for (int i = 1; i <= n - k - 1; ++i)
        cout << i << ' ';
    int l = n - k;
    int r = n;
    while (l <= r) {
        cout << l << ' ';
        ++l;
        if (l <= r)
            cout << r << ' ';
        --r;
    }
    return 0;
}

