#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 200111;
int n, q, nId, res[MN], cnt[11];
map< pair<int,int>, int > id;
vector< pair<int,int> > rows[MN], cols[MN], diag1[MN], diag2[MN];

void process(vector< pair<int,int> >& x) {
    if (x.size() < 2) return ;

    sort(x.begin(), x.end());
    REP(t,x.size()) {
        int u = id[x[t]];
        if (t == 0 || t == x.size() - 1)
            res[u] += 1;
        else
            res[u] += 2;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> q) {
        FOR(i,1,n) rows[i].clear();
        FOR(i,1,n) cols[i].clear();
        FOR(i,1,n+n) diag1[i].clear();
        FOR(i,1,n+n) diag2[i].clear();
        memset(res, 0, sizeof res);
        memset(cnt, 0, sizeof cnt);
        id.clear();

        nId = 0;
        FOR(i,1,q) {
            int u, v; cin >> u >> v;
            id[make_pair(u, v)] = ++nId;

            auto cur = make_pair(u, v);
            rows[u].push_back(cur);
            cols[v].push_back(cur);
            diag1[u+v].push_back(cur);
            diag2[u-v+n].push_back(cur);
        }

        FOR(i,1,n+n) {
            process(rows[i]);
            process(cols[i]);
            process(diag1[i]);
            process(diag2[i]);
        }

        FOR(i,1,q) cnt[res[i]] += 1;

        FOR(i,0,8) cout << cnt[i] << ' '; cout << endl;
    }
    return 0;
}
