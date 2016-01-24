#include <bits/stdc++.h>
#define int long long
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

struct Res {
    int val;
    vector< pair<int,int> > trace;

    friend ostream& operator << (ostream& cout, Res& r) {
        cout << r.val << endl;
        cout << SZ(r.trace) << endl;
        for(auto p : r.trace) {
            cout << p.first << ' ' << p.second << endl;
        }
        return cout;
    }
} res;

const int MN = 2011;
int na, nb, a[MN], b[MN], suma, sumb;

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> na) {
        FOR(i,1,na) cin >> a[i];
        cin >> nb;
        FOR(i,1,nb) cin >> b[i];

        suma = 0; FOR(i,1,na) suma += a[i];
        sumb = 0; FOR(i,1,nb) sumb += b[i];

        // do not swap
        res.val = llabs(suma - sumb);
        res.trace.clear();

        // swap 1
        FOR(i,1,na) FOR(j,1,nb) {
            ll cura = suma - a[i] + b[j];
            ll curb = sumb + a[i] - b[j];

            ll cur = llabs(cura - curb);
            if (cur < res.val) {
                res.val = cur;
                res.trace.clear();
                res.trace.push_back(make_pair(i, j));
            }
        }
        // swap 2
        vector< pair<int, pair<int,int> > > alla;
        FOR(x,1,na) FOR(y,x+1,na) {
            alla.push_back(make_pair(2*(a[x] + a[y]), make_pair(x, y)));
        }
        sort(alla.begin(), alla.end());

        FOR(u,1,nb) FOR(v,u+1,nb) {
            ll t = suma - sumb + 2*(b[u] + b[v]);
            auto it = lower_bound(alla.begin(), alla.end(),
                    make_pair(t, make_pair(0LL, 0LL)));

            if (it != alla.end()) {
                ll cur = llabs(t - it->first);
                if (cur < res.val) {
                    res.val = cur;
                    res.trace.clear();
                    res.trace.push_back(make_pair(it->second.first, u));
                    res.trace.push_back(make_pair(it->second.second, v));
                }
            }
            if (it != alla.begin()) {
                --it;
                ll cur = llabs(t - it->first);
                if (cur < res.val) {
                    res.val = cur;
                    res.trace.clear();
                    res.trace.push_back(make_pair(it->second.first, u));
                    res.trace.push_back(make_pair(it->second.second, v));
                }
            }
        }

        // result
        cout << res << endl;
    }
}
