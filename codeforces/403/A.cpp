#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int n, p;
vector< pair<int,int> > res;

int next(int u) {
    if (u == n) return 1;
    else return u + 1;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int test; cin >> test;
    while (test--) {
        cin >> n >> p;
        res.clear();

        FOR(i,1,n) res.push_back(make_pair(i, next(i)));
        FOR(i,1,n) res.push_back(make_pair(i, next(next(i))));

        FOR(len,3,n-1)
            FOR(i,1,n) {
                if (p == 0) break;
                --p;
                int j = i + len; while (j > n) j -= n;
                res.push_back(make_pair(i, j));
            }
        for(auto p : res) cout << p.first << ' ' << p.second << endl;
        cout << endl;
    }
    return 0;
}
