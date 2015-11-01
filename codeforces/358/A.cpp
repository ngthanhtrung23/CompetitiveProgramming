
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

int n;
int x[1011];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> x[i];
        bool ok = true;
        FOR(i,1,n-1)
            FOR(j,i+1,n-1) {
                int l = x[i], r = x[i+1];
                int u = x[j], v = x[j+1];

                if (l > r) swap(l, r);
                if (u > v) swap(u, v);

                if (v <= l) continue;
                if (r <= u) continue;
                if (l <= u && v <= r) continue;
                if (u <= l && r <= v) continue;

                ok = false;
            }
        cout << (ok ? "no" : "yes") << endl;
    }
}
