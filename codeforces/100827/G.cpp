
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

int a[111], f[111][111];

int grundy(int l, int r) {
    if (l > r) return 0;
    if (l == r) return 1;
    if (f[l][r] >= 0) return f[l][r];

    set<int> all;

    FOR(u,l,r) {
        if (u == l) {
            if (a[u] >= a[u+1]) {
                if (a[u+1] == 1 && u+1 == r) continue;
                all.insert(grundy(u+1, r));
            }
        }
        else if (u == r) {
            if (a[u] >= a[u-1]) {
                if (a[u-1] == 1 && u-1 == l) continue;
                all.insert(grundy(l, u-1));
            }
        }
        else {
            if (a[u] >= a[u-1] && a[u] >= a[u+1]) {
                if (a[u-1] == 1 && u-1 == l) continue;
                if (a[u+1] == 1 && u+1 == r) continue;
                all.insert(grundy(l, u-1) ^ grundy(u+1, r));
            }
        }
    }

    int res = 0;
    while (all.count(res)) ++res;
    return f[l][r] = res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    while (ntest--) {
        int n; cin >> n;
        FOR(i,1,n) cin >> a[i];
        if (n == 1) {
            cout << "Alice" << endl; // easy win
            continue;
        }
        memset(f, -1, sizeof f);
        cout << (grundy(1, n) ? "Alice" : "Bob") << endl;
    }
}
