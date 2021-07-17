#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e6 + 6;
int f[maxn][2];
char a[maxn];
int n;
int cost(int a, int b) {
    if (a == b) return 0;
    if (a == 0) return 1;
    return -1;
}
int calc(int i, int last) {
    if (i > n)
        return 0;
    int &res = f[i][last];
    if (res != -1) return res;
    if (a[i] != '?')
        return res = calc(i + 1, a[i] - 'a') + cost(last, a[i] - 'a');
    res = max(calc(i + 1, 0) + cost(last, 0), calc(i + 1, 1) + cost(last, 1));
    return res;
}
int main() {
#ifdef LDT
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    cin >> (a + 1);
    memset(f, -1, sizeof(f));
    if (a[1] == '?')
        cout << max(calc(2, 0), calc(2, 1));
    else 
        cout << calc(2, a[1] - 'a');
    return 0;
}

