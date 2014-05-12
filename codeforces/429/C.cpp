#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

#define TWO(x) (1<<(x))

int nOne, n, a[33];
vector<int> sum[1011];
bool f[22][44][TWO(13)];

bool solve() {
    if (n > 12) return false;
    if (n == 0) return nOne == 1;
    sort(a, a+n);

    memset(f, false, sizeof f);
    f[0][nOne][0] = true;

    REP(mask,TWO(n)) {
        int cur = 0;
        REP(i,n) if (mask & TWO(i)) cur += a[i];
        sum[cur].push_back(mask);
    }

    FOR(i,0,n-1) FOR(k,0,nOne) REP(mask,TWO(n))
    if (f[i][k][mask]) {
        int val = a[i] - 1;
        FOR(use_one,0,min(k,val)) {
            REP(t,sum[val-use_one].size()) {
                int mask2 = sum[val-use_one][t];
                if (use_one + __builtin_popcount(mask2) == 1) continue;
                if ((mask & mask2) == mask2) {
                    f[i+1][k-use_one][mask - mask2 + TWO(i)] = true;
                }
            }
        }
    }

    return f[n][0][TWO(n-1)];
}

int main() {
    ios :: sync_with_stdio(false);
    int x;
    while (cin >> x) {
        nOne = 0;
        n = 0;
        FOR(i,0,1000) sum[i].clear();
        while (x--) {
            int u; cin >> u;
            if (u == 1) ++nOne;
            else a[n++] = u;
        }

        if (solve()) cout << "YES"; else cout << "NO";
        cout << endl;
    }
    return 0;
}