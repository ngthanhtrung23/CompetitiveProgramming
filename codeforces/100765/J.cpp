
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

const int inf = 1000111;
struct Matching {
    int n;
    vector<int> matchL, matchR, dist;
    vector<bool> seen;
    vector< vector<int> > ke;

    Matching(int n) : n(n), matchL(n+1), matchR(n+1), dist(n+1), seen(n+1, false), ke(n+1) {}

    void addEdge(int u, int v) {
        ke[u].push_back(v);
    }

    bool bfs() {
        queue<int> qu;
        for(int u = 1; u <= n; ++u)
            if (!matchL[u]) {
                dist[u] = 0;
                qu.push(u);
            } else dist[u] = inf;
        dist[0] = inf;

        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            for(__typeof(ke[u].begin()) v = ke[u].begin(); v != ke[u].end(); ++v) {
                if (dist[matchR[*v]] == inf) {
                    dist[matchR[*v]] = dist[u] + 1;
                    qu.push(matchR[*v]);
                }
            }
        }
        return dist[0] != inf;
    }

    bool dfs(int u) {
        if (u) {
            for(__typeof(ke[u].begin()) v = ke[u].begin(); v != ke[u].end(); ++v)
                if (dist[matchR[*v]] == dist[u] + 1 && dfs(matchR[*v])) {
                    matchL[u] = *v;
                    matchR[*v] = u;
                    return true;
                }
            dist[u] = inf;
            return false;
        }
        return true;
    }

    int match() {
        int res = 0;
        while (bfs()) {
            for(int u = 1; u <= n; ++u)
                if (!matchL[u])
                    if (dfs(u)) ++res;
        }
        return res;
    }
};

int n;
ll m, a[311], b[311], x[311*311];
set<ll> all[311];
ll res[311];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        set<ll> nums;
    
        FOR(i,1,n) {
            cin >> a[i] >> b[i];
            all[i].clear();

            if (a[i] == 0) {
                if (1 <= b[i] && b[i] <= m) {
                    nums.insert(b[i]);
                    all[i].insert(b[i]);
                }
            }
            else if (a[i] > 0) {
                ll lb = (1 - b[i]) / a[i] - 2;
                ll ub = (m - b[i]) / a[i] + 2;

                if (lb < 0) lb = 0;

                FOR(k,lb,ub) {
                    ll cur = a[i]*k + b[i];

                    if (cur < 1 || cur > m) continue;
                    nums.insert(cur);
                    all[i].insert(cur);

                    if (SZ(all[i]) > n) break;
                }
            }
            else { // a[i] < 0
                ll ub = (b[i] - 1) / -a[i] + 2;
                ll lb = (b[i] - m) / -a[i] - 2;

                if (lb < 0) lb = 0;

                FOR(k,lb,ub) {
                    ll cur = a[i]*k + b[i];
                    if (cur < 1 || cur > m) continue;

                    nums.insert(cur);
                    all[i].insert(cur);

                    if (SZ(all[i]) > n) break;
                }
            }
//            DEBUG(i);
//            for(auto t : all[i]) cout << t << ' '; cout << endl;
        }
        int cnt = 0;
        for(auto t : nums) {
            x[++cnt] = t;
        }
//        PR(x, cnt);
        Matching mat(max(n, cnt));
        FOR(i,1,n) {
            FOR(j,1,cnt)
                if (all[i].count(x[j])) {
                    mat.addEdge(i, j);
                }
        }
        int r = mat.match();

        nums.clear();
        FOR(i,1,n) {
            int j = mat.matchL[i];
            if (j) {
                res[i] = x[j];
                nums.insert(x[j]);
            }
        }
        FOR(i,1,n) {
            if (!res[i]) {
                res[i] = 1;
                while (nums.count(res[i])) ++res[i];

                nums.insert(res[i]);
            }
        }
        FOR(i,1,n) cout << res[i] << ' '; cout << endl;
    }
}
