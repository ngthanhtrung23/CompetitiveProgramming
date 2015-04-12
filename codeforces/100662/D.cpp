
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

int main() {
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int x, r, c; cin >> x >> r >> c;
        if (r > c) swap(r, c);
        bool res;
        if (x >= 7 || (r*c) % x) res = true;
        else if (x > r && x > c) res = true;
        else if (x == 1) res = false;
        else if (x == 2) res = false;
        else if (x == 3) {
            if (r == 1) res = true;
            else res = false;
        }
        else if (x == 4) {
            if (r == 1) res = true;
            else if (r == 2) res = true;
            else res = false;
        }
        else if (x == 5) {
            if (r <= 2) res = true;
            else if (r == 3 && c == 5) res = true;
            else res = false;
        }
        else if (x == 6) {
            if (r <= 2) res = true;
            else if (r == 3) res = true;
            else res = false;
        }
        else {
            assert(false);
        }
        cout << "Case #" << test << ": " << (res ? "RICHARD" : "GABRIEL") << endl;
    }
    return 0;
}

