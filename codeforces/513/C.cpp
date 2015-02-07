
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

int n;
long long L[11], R[11];

long long choose(long long l, long long r, long long u, long long v) {
    if (u > v) return 0;
    if (v < l || r < u) return 0;
    l = max(l, u);
    r = min(r, v);

    return r - l + 1;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(12);
    while (cin >> n) {
        FOR(i,1,n) cin >> L[i] >> R[i];
        long double ways = 1;
        FOR(i,1,n) ways *= R[i] - L[i] + 1;

//        DEBUG(ways);

        long double sum = 0;
        FOR(res,1,10000) {
            // has greater
            FOR(i,1,n) {
                long double cur = choose(L[i], R[i], res+1, 10000);

                long double any = 1;
                FOR(j,1,n) if (j != i) {
                    any *= choose(L[j], R[j], 1, res);
                }
                long long bad = 1;
                FOR(j,1,n) if (j != i) {
                    bad *= choose(L[j], R[j], 1, res-1);
                }

                sum += res * cur / ways * (any - bad);
            }
            // no greater
            {
                REP(mask,1<<n) if (__builtin_popcount(mask) > 1) {
                    long double cur = 1.0;
                    FOR(i,1,n)
                        if (mask & (1<<(i-1))) {
                            cur *= choose(L[i], R[i], res, res);
                        }
                        else {
                            cur *= choose(L[i], R[i], 1, res-1);
                        }
                    sum += res * cur / ways;
                }
            }
        }
        cout << sum << endl;
    }
    return 0;
}
