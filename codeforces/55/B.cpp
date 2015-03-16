
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

ll res = 1e18;
void attempt(vector<ll> x, vector<char> c, int turn) {
    if (x.size() == 1) {
        res = min(res, x[0]);
        return ;
    }

    vector<ll> xx;
    REP(i,x.size()) FOR(j,i+1,x.size()-1) {
        xx.clear();
        if (c[turn] == '+') xx.push_back(x[i] + x[j]);
        else xx.push_back(x[i] * x[j]);

        REP(k,x.size()) if (k != i && k != j) xx.push_back(x[k]);

        attempt(xx, c, turn + 1);
    }
}

int main() {
    ll a, b, c, d;
    while (cin >> a >> b >> c >> d) {
        res = 1e18;
        vector<ll> x {a, b, c, d};
        char u, v, w; cin >> u >> v >> w;
        vector<char> y {u, v, w};

        attempt(x, y, 0);
        cout << res << endl;
    }
    return 0;
}
