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

int n, k, a[1011], x[1011];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> k) {
        FOR(i,1,n) cin >> a[i];
        int best = n, save = 0;
        FOR(first,1,1000) {
            x[1] = first;
            FOR(i,2,n) x[i] = x[i-1] + k;

            int cur = 0;
            FOR(i,1,n) if (x[i] != a[i]) ++cur;

            if (cur < best) best = cur, save = first;
        }
        x[1] = save;
        FOR(i,2,n) x[i] = x[i-1] + k;

        cout << best << endl;
        FOR(i,1,n) {
            if (a[i] < x[i]) cout << "+ " << i << ' ' << x[i] - a[i] << endl;
            if (a[i] > x[i]) cout << "- " << i << ' ' << a[i] - x[i] << endl;
        }
    }
    return 0;
}
