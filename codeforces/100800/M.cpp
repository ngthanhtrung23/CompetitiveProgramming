
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

const int MN = 1011;

ll t[MN], x[MN];
int m, n;

bool equal(ll s1, ll s2, ll t1, ll t2) {
    return (s1*t2 == s2*t1)
        && abs(s1 / (long double) s2 - t1 / (long double) t2) < 1e-6;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n) {
        FOR(i,1,m) cin >> t[i];
        FOR(i,1,n) cin >> x[i];

        vector<ll> res;
        FOR(i,1,n-m+1) {
            // 1st stone we saw is x[i]
            // speed = s1 / s2
            ll s1 = x[i+1] - x[i];
            ll s2 = t[2] - t[1];

            bool good = true;
            FOR(j,2,m-1) {
                // speed = t1 / t2
                ll t1 = x[i+j] - x[i+j-1];
                ll t2 = t[j+1] - t[j];

                if (!equal(s1, s2, t1, t2)) {
                    good = false;
                    break;
                }
            }
            if (good) res.push_back(x[i+1] - x[i]);
        }
        sort(res.begin(), res.end());
        res.resize(unique(res.begin(), res.end()) - res.begin());
        cout << res.size() << '\n';
        REP(i,SZ(res)) cout << res[i] << ' '; cout << '\n';
    }
}

