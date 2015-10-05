
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

ll best, savex, savey, n;

ll get(ll x) {
    ll y = n / (5*x);
    while (5 * x * y < n) ++y;

    ll curx = 44 * x + 4;
    ll cury = 10 * y + 2;
    ll cur = curx * cury;
    if (curx < cury) swap(curx, cury);

    if (cur < best || cur == best && curx - cury < savex - savey) {
        best = cur;
        savex = curx;
        savey = cury;
    }
    return cur;
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n;
        best = 1000111000111000111LL;
        savex = savey = -1;

        for(ll x = 1; x*x <= n; ++x)
            get(x);

        if (savex < savey) swap(savex, savey);

        cout << savex << " X " << savey << " = " << best << '\n';
    }
}

