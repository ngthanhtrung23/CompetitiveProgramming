
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))
using namespace std;

int nLucky, lucky[1000111];

long long intersect(long long u, long long v, long long x, long long y) {
    if (v < x || y < u) return 0;
    return min(y, v) - max(x, u) + 1;
}

int main() {
    FOR(len,1,9) REP(mask,TWO(len)) {
        int now = 0;
        REP(i,len) if (CONTAIN(mask,i)) now = now * 10 + 7; else now = now * 10 + 4;
        lucky[++nLucky] = now;
    }
    sort(lucky+1, lucky+nLucky+1);
    lucky[nLucky+1] = 1000111000;

    long long al, ar, bl, br;
    int k;
    while (cin >> al >> ar >> bl >> br >> k) {
        long long res = 0;
        FOR(i,1,nLucky-k+1) {
            long long x = lucky[i], y = lucky[i+k-1];
            long long z = lucky[i-1], t = lucky[i+k];

            // a <= b
            res += intersect(z+1, x, al, ar) * intersect(y, t-1, bl, br);
            // b < a
            res += intersect(z+1, x, bl, br) * intersect(y, t-1, al, ar);

            if (k == 1) res -= intersect(x, x, al, ar) * intersect(x, x, bl, br);
        }
        cout << (fixed) << setprecision(12) << res / (double) (ar - al + 1) / (br - bl + 1) << endl;
    }
    return 0;
}

