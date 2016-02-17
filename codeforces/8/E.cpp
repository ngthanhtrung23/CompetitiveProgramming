
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 55;
char a[MN];
ll f[55][2][2];
int n;

ll get() {
    memset(f, 0, sizeof f);
    f[0][0][0] = 1;
    int mid = n / 2 + n % 2;

    FOR(i,0,mid-1) REP(lessRev,2) REP(lessInv,2) {
        int left = i + 1;
        int right = n - left + 1;

        ll cur = f[i][lessRev][lessInv];
        if (!cur) continue;

        REP(x,2) REP(y,2) {
            if (a[left] != '?' && a[left] != x + '0') continue;
            if (a[right] != '?' && a[right] != y + '0') continue;
            if (left == right && x != y) continue;
            if (left == 1 && x != 0) continue;

            if (!lessRev && x > y) continue;
            if (!lessInv && x > (1-y)) continue;

            int lessRev2 = lessRev;
            int lessInv2 = lessInv;
            if (x < y) lessRev2 = 1;
            if (x < (1 - y)) lessInv2 = 1;

            f[i+1][lessRev2][lessInv2] += cur;
        }
    }
    ll res = 0;
    REP(x,2) REP(y,2) res += f[mid][x][y];
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    ll k;
    while (cin >> n >> k) {
        ++k;
        memset(a, '?', sizeof a);

        ll all = get();
        if (all < k) {
            cout << -1 << endl;
            continue;
        }

        FOR(i,1,n) {
            a[i] = '0';
            ll t = get();
            if (t >= k) {
            }
            else {
                k -= t;
                a[i] = '1';
            }
        }
        FOR(i,1,n) cout << a[i]; cout << endl;
    }
}
