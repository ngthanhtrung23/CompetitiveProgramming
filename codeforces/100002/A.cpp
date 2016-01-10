
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

ll k, m;
int dn[111], dm[111], ln, lm;

int cnt_digit(ll n) {
    if (n == 0) return 1;
    int res = 0;
    while (n > 0) {
        ++res;
        n /= 10;
    }
    return res;
}
void init(ll n, int d[], int&len) {
    memset(d, 0, sizeof d);
    len = cnt_digit(n);
    FORD(i,len,1) {
        d[i] = n % 10;
        n /= 10;
    }
}

ll f[22][2];
ll getSmall(ll len) {
    memset(f, 0, sizeof f);
    f[0][0] = 1;
    FOR(i,0,len-1) FOR(lower,0,1) {
        FOR(add,0,9) if (i > 0 || add > 0) {
            if (lower == 0 && add > dm[i+1]) continue;
            int lower2 = lower;
            if (add < dm[i+1]) lower2 = 1;

            f[i+1][lower2] += f[i][lower];
        }
    }

    if (len < lm) return f[len][0] + f[len][1];
    return f[len][1];
}

ll g[22][2][2];

ll getEqual() {
    memset(g, 0, sizeof g);
    g[0][0][0] = 1;
    FOR(i,0,ln-1) FOR(lowerN,0,1) FOR(lowerM,0,1) {
        FOR(add,0,9) if (i > 0 || add > 0) {
            if (lowerN == 0 && add > dn[i+1]) continue;
            if (lowerM == 0 && add > dm[i+1]) continue;

            int lowerN2 = lowerN; if (add < dn[i+1]) lowerN2 = 1;
            int lowerM2 = lowerM; if (add < dm[i+1]) lowerM2 = 1;

            g[i+1][lowerN2][lowerM2] += g[i][lowerN][lowerM];
        }
    }
    if (ln < lm) return g[ln][1][0] + g[ln][1][1];
    else return g[ln][1][1];
}

ll get(ll n) {
    ++n;
    init(n, dn, ln);
    init(m, dm, lm);

//    PR(dn, ln);
//    PR(dm, lm);

    ll res = 0;
    FOR(len,1,ln-1) {
        res += getSmall(len);
    }
    res += getEqual();
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("amusing.in", "r", stdin);
    freopen("amusing.out", "w", stdout);
    while (cin >> m >> k) {
        ll t = get(11);

        ll l = m, r = 1000111000111000111LL;
        ll res = r;
        while (l <= r) {
            ll mid = (l + r) >> 1;
            if (get(mid) >= k-1) {
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        if (res == 1000111000111000111LL) cout << 0 << endl;
        else {
            if (get(res) > k-1) cout << 0 << endl;
            else cout << res << endl;
        }
    }
}
