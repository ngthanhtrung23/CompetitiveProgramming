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

const int MN = 300111;
set<int> blocked[MN];
int n, m, k;
int visited[MN];

void init() {
    FOR(i,1,n) blocked[i].clear();
}

int cnt() {
    memset(visited, 0, sizeof visited);
    int res = 0;

    set<int> cur;
    FOR(i,1,n) cur.insert(i);

    FOR(i,1,n) if (!visited[i]) {
        visited[i] = ++res;
        cur.erase(i);
        queue<int> qu; qu.push(i);
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            vector<int> added;
            for(int v : cur) {
                if (blocked[u].count(v)) continue;

                visited[v] = visited[u];
                added.push_back(v);
                qu.push(v);
            }
            for(auto x : added) cur.erase(x);
        }
    }
    return res;
}

int good[MN];

bool solve() {
    int t = cnt();
    if (t > 1) return false;

    auto save = blocked[1];
    FOR(i,2,n) blocked[1].insert(i);
    t = cnt();
    blocked[1] = save;

    if (t - 1 > k) return false;

    memset(good, 0, sizeof good);

    FOR(i,2,n) if (!blocked[1].count(i)) {
        good[visited[i]] = true;
    }
    good[visited[1]] = true;

    FOR(i,1,t) if (!good[i]) return false;

    if (n - 1 - SZ(blocked[1]) < k) return false;

    return true;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (scanf("%lld%lld%lld", &n, &m, &k) == 3) {
        init();
        FOR(i,1,m) {
            int u, v; scanf("%lld%lld", &u, &v);
            blocked[u].insert(v);
            blocked[v].insert(u);
        }
        cout << (solve() ? "possible" : "impossible") << endl;
    }
}
