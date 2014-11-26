#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int m, n, x, y, z, p;
pair<int,int> a[100111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> m >> n >> x >> y >> z >> p) {
        FOR(i,1,p) cin >> a[i].first >> a[i].second;
        x %= 4;
        while (x--) {
            swap(m, n);
            FOR(i,1,p) {
                swap(a[i].first, a[i].second);
                a[i].second = n - a[i].second + 1;
            }
        }
        y %= 2;
        while (y--) {
            FOR(i,1,p) {
                a[i].second = n - a[i].second + 1;
            }
        }
        z %= 4;
        while (z--) {
            swap(m, n);
            FOR(i,1,p) {
                swap(a[i].first, a[i].second);
                a[i].first = m - a[i].first + 1;
            }
        }
        FOR(i,1,p) cout << a[i].first << ' ' << a[i].second << endl;
    }
    return 0;
}

