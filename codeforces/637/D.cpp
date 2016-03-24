
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 200111;
int n, m, s, d, a[MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> m >> s >> d) {
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1);
        a[0] = -1;

        int can = a[1] - 1 + d;
        int ok = 1;
        
        int pos = 0;
        vector< pair<string,int> > res;
        FOR(i,1,n) {
            if (i == 1 && a[i] <= s) {
                ok = 0;
                break;
            }
            if (a[i] >= can) {
                ok = 0;
                break;
            }
            if (i == n) break;
            if (a[i+1] - a[i] >= s + 2) {
                can = a[i+1] - 1 + d;

                // jump over i
                // walk until that point
                int to = max(pos + s, a[i] + 1 - d);
                res.push_back(make_pair("RUN", to - pos));
                pos = to;
                // jump
                res.push_back(make_pair("JUMP", a[i] + 1 - pos));
                pos = a[i] + 1;
            }
        }
        if (!ok) {
            cout << "IMPOSSIBLE" << endl;
            continue;
        }
        if (pos < a[n]) {
            int to = max(pos + s, a[n] + 1 - d);
            res.push_back(make_pair("RUN", to - pos));
            pos = to;
            // jump
            res.push_back(make_pair("JUMP", a[n] + 1 - pos));
            pos = a[n] + 1;
        }
        if (pos < m) {
            res.push_back(make_pair("RUN", m - pos));
        }
        for(auto p : res) cout << p.first << ' ' << p.second << '\n';
        cout << endl;
    }
}
