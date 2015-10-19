
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

vector< vector<int> > gen(int n) {
    if (n == 1) {
        vector<int> t; t.push_back(1);
        vector< vector<int> > res; res.push_back(t);
        return res;
    }

    auto last = gen(n-1);
    vector< vector<int> > res;

    REP(i,SZ(last)) {
        if (i % 2 == 1) {
            FOR(pos,0,n-1) {
                vector<int> cur = last[i];
                cur.insert(cur.begin() + pos, n);
                res.push_back(cur);
            }
        }
        else {
            FORD(pos,n-1,0) {
                vector<int> cur = last[i];
                cur.insert(cur.begin() + pos, n);
                res.push_back(cur);
            }
        }
    }

    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        vector<vector<int> > res = gen(n);
        REP(i,SZ(res)) {
            REP(j,SZ(res[i])) cout << res[i][j] << ' ';
            cout << '\n';
        }
    }
}

