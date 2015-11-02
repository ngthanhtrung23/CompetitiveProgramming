
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

int n, k, l, r, sall, sk;
int a[1011];

bool can(int k, int sum, int l, int r) {
    return k*l <= sum && sum <= k*r;
}

bool construct(int x) {
    // first k
    if (!can(k, sk, x, r)) return false;
    if (!can(n-k, sall-sk, l, x)) return false;

    int need = sk;
    FOR(i,1,k) {
        a[i] = x;
        need -= a[i];
    }

    FOR(i,1,k) {
        int add = min(r - a[i], need);
        a[i] += add;
        need -= add;
    }
    assert(need == 0);

    need = sall - sk;
    FOR(i,k+1,n) {
        a[i] = l;
        need -= l;
    }
    FOR(i,k+1,n) {
        int add = min(x - a[i], need);
        a[i] += add;
        need -= add;
    }
    assert(need == 0);
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k >> l >> r >> sall >> sk) {
        FOR(x,l,r) {
            if (construct(x)) {
                FOR(i,1,n) cout << a[i] << ' ';
                cout << endl;
                break;
            }
        }
    }
}
