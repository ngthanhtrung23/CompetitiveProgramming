
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define dec __dec
using namespace std;

const int MN = 100111;
int n, q, a[MN], inc[MN], dec[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> q) {
        FOR(i,1,n) cin >> a[i];
        FORD(i,n,1) {
            if (i == n) inc[i] = dec[i] = n;
            else {
                if (a[i] <= a[i+1]) inc[i] = inc[i+1];
                else inc[i] = i;

                if (a[i] >= a[i+1]) dec[i] = dec[i+1];
                else dec[i] = i;
            }
        }
        while (q--) {
            int l, r; cin >> l >> r;
            int u = inc[l];
            if (u >= r) cout << "Yes";
            else if (dec[u] >= r) cout << "Yes";
            else cout << "No";
            cout << '\n';
        }
    }
    return 0;
}
