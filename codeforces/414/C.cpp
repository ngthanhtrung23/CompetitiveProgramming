#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 2000111;

int n, a[MN], b[MN], tmp[MN];
long long f[2][33];

void init(int l, int r, int level, int turn) {
    if (l == r) {
        return ;
    }
    int mid = (l + r) >> 1;
    init(l, mid, level - 1, turn);
    init(mid+1, r, level - 1, turn);

    int i = l, j = mid + 1, cur = l;
    while (i <= mid || j <= r) {
        if (i > mid) {
            b[cur++] = a[j++];
        }
        else if (j > r) {
            b[cur++] = a[i++];
            f[turn][level] += j - (mid+1);
        }
        else if (a[i] <= a[j]) {
            b[cur++] = a[i++];
            f[turn][level] += j - (mid+1);
        }
        else {
            b[cur++] = a[j++];
        }
    }
    FOR(i,l,r) a[i] = b[i];
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,(1<<n)) {
            scanf("%d", &a[i]);
            tmp[i] = a[i];
        }
        memset(f, 0, sizeof f);

        init(1, 1<<n, n, 0);
        FOR(i,1,(1<<n)) a[i] = tmp[(1<<n) - i + 1];
        init(1, 1<<n, n, 1);

        // PR(a, 1<<n);
        // PR0(f[0], n+1);
        // PR0(f[1], n+1);

        long long res = 0;
        FOR(i,0,n) res += f[0][i];

        int q; scanf("%d", &q);
        while (q--) {
            int k; scanf("%d", &k);
            FOR(i,0,k) {
                res -= f[0][i];
                swap(f[0][i], f[1][i]);
                res += f[0][i];
            }
            printf("%I64d\n", res);
        }
    }
    return 0;
}
