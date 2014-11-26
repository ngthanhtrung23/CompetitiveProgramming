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

int a[1000111], p, x;

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> p >> x) {
        bool ok = false;
        FOR(last,0,9) if (p > 1 || last > 0) {
            a[p] = last;
            int rem = 0;
            FORD(i,p-1,0) {
                int cur = a[i+1] * x + rem;
                a[i] = cur % 10;
                rem = cur / 10;
            }
            if (rem == 0 && a[1] > 0 && a[p] == a[0]) {
                FOR(i,1,p) cout << a[i];
                cout << endl;
                ok = true;
                break;
            }
        }
        if (!ok) cout << "Impossible" << endl;
    }
    return 0;
}

