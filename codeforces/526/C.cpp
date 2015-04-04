
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
using namespace std;

ll C, hr, hb, wr, wb;

ll f(ll x) {
    return hr*x + (C - wr*x) / wb * hb;
}

int main() {
    while (cin >> C >> hr >> hb >> wr >> wb) {
        ll res = 0;
        REP(turn,2) {
            ll left = 0, right = C / wr;
            res = max(res, max(f(left), f(right)));
            REP(turn,10000) {
                ll x1 = (left + left + right) / 3;
                ll x2 = (left + right + right) / 3;

                ll y1 = f(x1), y2 = f(x2);

                res = max(res, max(y1, y2));

                if (y1 > y2) right = x2;
                else left = x1;
            }
            REP(x,min(10000000LL,C/wr))
                res = max(res, f(x));
            FORD(x,C/wr,max(0LL,C/wr-10000000LL))
                res = max(res, f(x));
            swap(hr, hb);
            swap(wr, wb);
        }
        cout << res << endl;
    }
    return 0;
}
