
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const int MN = 1011;
ll W, a[MN][MN], diag[2][MN][MN];
int n;

ll get(int i1, int j1, int i2, int j2, int sz) {
    ll res = diag[0][i2][j2] - diag[0][i1-1][j1-1]
            + diag[1][i2][j1] - diag[1][i1-1][j2+1];
    if (sz & 1) {
        res -= a[i1 + (sz >> 1)][j1 + (sz >> 1)];
    }
    return res;
}

bool check(int sz) {
    FOR(i1,1,n-sz+1) FOR(j1,1,n-sz+1) {
        ll cur = get(i1, j1, i1+sz-1, j1+sz-1, sz);
        if (cur <= W) return true;
    }
    return false;
}

int getOdd() {
    int res = -1;
    int left = 1, right = n / 2;
    if (right * 2 + 1 > n) --right;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(mid * 2 + 1)) res = mid * 2 + 1, left = mid + 1;
        else right = mid - 1;
    }
    return res;
}

int getEven() {
    int res = 0, left = 0, right = n / 2;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(mid * 2)) res = mid * 2, left = mid + 1;
        else right = mid - 1;
    }
    return res;
}

int main() {
    int ntest; scanf("%d", &ntest);
    while (ntest--) {
        scanf("%d", &n);
        scanf("%I64d", &W);
        FOR(i,1,n) FOR(j,1,n) {
            scanf("%I64d", &a[i][j]);
            diag[0][i][j] = diag[0][i-1][j-1] + a[i][j];
            diag[1][i][j] = diag[1][i-1][j+1] + a[i][j];
        }
        int res = max(getOdd(), getEven());
        if (res == 0) {
            FOR(i,1,n) FOR(j,1,n) if (a[i][j] <= W) res = 1;
        }
        printf("%d\n", res);
    }
}
