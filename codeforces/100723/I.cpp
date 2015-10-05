
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

int n, k, a[55][55], pos[55];

int getDistance(int u, int v) {
    if (u > v) swap(u, v);
    return min(v - u, k + u - v);
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n >> k;
        FOR(i,1,n) FOR(j,1,k) cin >> a[i][j];

        int res = 0;
        FOR(i,1,n) {
            vector< pair<int,int> > pos;
            FOR(j,1,k) if (a[i][j] >= 0) pos.push_back(make_pair(a[i][j], j));
            sort(pos.begin(), pos.end());

            if (pos.empty()) continue;

            res += (i-1) * 20 * SZ(pos);

            int cur = 1;
            for(auto p : pos) {
                res += 5 * getDistance(cur, p.second);
                cur = p.second;
            }
        }
        cout << res << '\n';
    }
}

