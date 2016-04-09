
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

int GI(int& x) {
    return scanf("%lld", &x);
}

const int MN = 100111;
int n;
vector< pair<int,int> > ke[MN];
int bit[MN], getIn[MN], getOut[MN], dfsNum, toParent[MN], father[22][MN], h[MN];

void dfs(int u, int fu) {
    father[0][u] = fu;

    getIn[u] = ++dfsNum;
    for(auto e : ke[u]) {
        int v = e.first;
        if (v == fu) continue;

        h[v] = h[u] + 1;
        toParent[v] = e.second;
        dfs(v, u);
    }
    getOut[u] = dfsNum;
}

void update(int x, int val) {
    for(; x < MN; x += x & -x)
        bit[x] += val;
}
int get(int x) {
    int res = 0;
    for(; x > 0; x -= x & -x)
        res += bit[x];
    return res;
}

void updateSeg(int l, int r, int val) {
    update(l, val);
    update(r+1, -val);
}

void initLCA() {
    FOR(t,1,20) {
        FOR(u,1,n)
            father[t][u] = father[t-1][ father[t-1][u] ];
    }
}

int lca(int u, int v) {
    if (u == v) return u;

    if (h[u] != h[v]) {
        if (h[u] > h[v]) swap(u, v);

        FORD(i,20,0) {
            int x = father[i][v];
            if (h[x] >= h[u]) v = x;
        }
    }
    if (u == v) return u;

    FORD(i,20,0)
        if (father[i][u] != father[i][v]) {
            u = father[i][u];
            v = father[i][v];
        }
    return father[0][u];
}

int getDist(int u, int v) {
    int l = lca(u, v);
    return get(getIn[u]) + get(getIn[v]) - 2*get(getIn[l]);
}

int res[MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v, c; GI(u); GI(v); GI(c);
            ke[u].emplace_back(v, c);
            ke[v].emplace_back(u, c);
        }
        dfsNum = 0;
        h[1] = 1;
        dfs(1, -1);

        memset(bit, 0, sizeof bit);
        FOR(i,2,n) {
            int l = getIn[i], r = getOut[i];
            updateSeg(l, r, toParent[i]);
        }

        initLCA();

        int q; GI(q);
        while (q--) {
            int typ; GI(typ);
            if (typ == 1) {
                int u, v, c;
                GI(u); GI(v); GI(c);
                if (v == father[0][u]) swap(u, v);

                updateSeg(getIn[v], getOut[v], -toParent[v]);
                toParent[v] = c;
                updateSeg(getIn[v], getOut[v], toParent[v]);
            }
            else {
                int k; GI(k);
                vector<int> p; p.resize(k);
                REP(i,k) GI(p[i]);

                int x = p[0], y = p[0], diam = 0;
                REP(i,k) res[i] = 0;

                FOR(i,1,k-1) {
                    int v = p[i];
                    int toX = getDist(v, x);
                    int toY = getDist(v, y);

                    res[i] = max(res[i], max(toX, toY));

                    if (toX > toY) {
                        if (toX > diam) {
                            diam = toX;
                            y = v;
                        }
                    }
                    else {
                        if (toY > diam) {
                            diam = toY;
                            x = v;
                        }
                    }
                }

                x = y = p.back(); diam = 0;
                FORD(i,k-2,0) {
                    int v = p[i];
                    int toX = getDist(v, x);
                    int toY = getDist(v, y);

                    res[i] = max(res[i], max(toX, toY));
                    if (toX > toY) {
                        if (toX > diam) {
                            diam = toX;
                            y = v;
                        }
                    }
                    else {
                        if (toY > diam) {
                            diam = toY;
                            x = v;
                        }
                    }
                }

                REP(i,k) printf("%lld ", res[i]); puts("");
            }
        }
    }
}
