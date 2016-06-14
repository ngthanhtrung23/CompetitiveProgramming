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

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

const int MN = 100111;

int n, h[MN];
vector<int> ke[MN];
int vao[MN], pref[MN];

int cmp(const int& u, const int& v) {
    if (h[u] == h[v]) return u < v;
    return h[u] > h[v];
}

void dfs1(int u) {
    for(int v : ke[u]) {
        h[v] = h[u] + 1;
        dfs1(v);
    }
}

int id[MN];
set< pair<int,int> > all;

void dfs2(int u) {
    if (id[u] >= 0) {
        all.insert(make_pair(id[u], u));
    }

    if (all.empty()) {
        throw 1;
    }
    if (all.begin()->second != pref[u]) {
        throw 1;
    }

    for(int v : ke[u]) {
        dfs2(v);
    }
    all.erase(make_pair(id[u], u));
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int m;
    while (GI(n) == 1 && GI(m) == 1) {
        FOR(i,1,n) ke[i].clear();
        memset(vao, 0, sizeof vao);
        memset(h, 0, sizeof h);

        vector<int> res;
        FOR(i,1,m) {
            int u, v; GI(u); GI(v);
            ke[u].push_back(v);
            vao[v]++;
        }
        FOR(v,1,n) if (!vao[v]) dfs1(v);

        FOR(i,1,n) {
            GI(pref[i]);
            res.push_back(pref[i]);
        }
        sort(res.begin(), res.end(), cmp);
        res.resize(unique(res.begin(), res.end()) - res.begin());

        memset(id, -1, sizeof id);
        REP(i,SZ(res)) {
            id[res[i]] = i + 1;
        }

        try {
            all.clear();
            FOR(v,1,n) if (!vao[v]) dfs2(v);

            printf("%lld\n", SZ(res));
            for(int u : res) printf("%lld\n", u);
        } catch (...) {
            puts("-1");
        }
    }
}
