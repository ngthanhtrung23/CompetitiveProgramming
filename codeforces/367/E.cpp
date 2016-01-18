
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

const ll MOD = 1e9 + 7;
const ll MOD2 = MOD * MOD;

ll f[2][333][333][2];  // xoay mang theo j
int n, m, x;

void update(ll& x, ll t) {
    x += t;
    if (x >= MOD2) x -= MOD2;
}

int main() {
    while (cin >> m >> n >> x) {
        if (m > n) {
            cout << 0 << endl;
        }
        else {
            // n >= m (nPoint >= nSeg)

            // f[i][opened][closed][t]
            // = # configurations: i positions
            //   # opened segments
            //   # closed segments
            //   t = has segment with l == i ?

            memset(f, 0, sizeof f);
            f[0][0][0][0] = 1;
            FOR(i,0,n-1) {
                int t = i % 2;

                FOR(opened,0,m) FOR(closed,0,opened) REP(good,2)
                    f[1-t][opened][closed][good] = 0;

                FOR(opened,0,m) FOR(closed,0,opened) REP(good,2) {
                    int good2 = good;
                    if (x == i+1) good2 = 1;

                    ll cur = f[t][opened][closed][good];
                    if (!cur) continue;

                    // do nothing at position (i+1)
                    update(f[1-t][opened][closed][good], cur);

                    // open some new segment at position (i+1)
                    update(f[1-t][opened+1][closed][good2], cur);

                    // close a segment at position (i+1)
                    if (opened > closed) {
                        update(f[1-t][opened][closed+1][good], cur);
                    }

                    // both open & close a segment
                    if (opened >= closed) {
                        update(f[1-t][opened+1][closed+1][good2], cur);
                    }
                }
            }

            ll res = f[n % 2][m][m][1] % MOD;
            FOR(i,1,m) {
                res = res * i % MOD;
            }
            cout << res << endl;
        }
    }
}
