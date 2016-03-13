
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 255;
struct DSU {
    int lab[MN];
    void init(int n) {
        REP(i,n+1) lab[i] = -1;
    }

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
};

int n, nGood, nBad;
int k, weight[MN];
int ke[MN][MN];

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int best, cntBest;
pair<int,ll> f[TWO(23) + 11];
int can[TWO(23) + 11], what[TWO(23) + 11];

void solve() {
    int left_from = 1, left_to = k / 2;
    int right_from = left_to + 1, right_to = k;
    int right_size = right_to - right_from + 1;

    // first half
    REP(s,TWO(left_to)) {
        if (s == 0) {
            f[s] = make_pair(0, 1LL);
        }
        else {
            // u = any on bit
            int u = 0; while (!CONTAIN(s,u)) ++u;
            
            // if we don't select u
            f[s] = f[s - TWO(u)];

            // if we select u, we can select any vertex in s2
            int s2 = 0;
            REP(v,left_to)
                if (CONTAIN(s,v) && v != u)
                    if (!ke[left_from + u][left_from + v]) s2 += TWO(v);

            int cur = f[s2].first + weight[left_from + u];
            if (cur > f[s].first) {
                f[s] = make_pair(cur, f[s2].second);
            }
            else if (cur == f[s].first) {
                f[s].second += f[s2].second;
            }
        }
    }

    int best = -1;
    ll cntBest = 0;

    // second half
    memset(can, 0, sizeof can);
    memset(what, 0, sizeof what);
    REP(s,TWO(right_size)) {
        if (s == 0) {
            // can we select set S from right half?
            can[s] = 1;
            
            // if we select set S from right, what is the set that we can select in left half?
            what[s] = TWO(left_to) - 1;
        }
        else {
            int u = 0; while (!CONTAIN(s,u)) ++u;
            can[s] = can[s - TWO(u)];
            REP(v,right_size) if (v != u) {
                if (CONTAIN(s,v) && ke[right_from + u][right_from + v]) {
                    can[s] = 0;
                    break;
                }
            }

            what[s] = what[s - TWO(u)];
            REP(v,left_to)
                if (ke[left_from + v][right_from + u] && CONTAIN(what[s], v)) {
                    what[s] -= TWO(v);
                }
        }
        if (!can[s]) continue;

        int right_weight = 0;
        REP(u,right_size) if (CONTAIN(s,u)) right_weight += weight[right_from + u];

        int cur = right_weight + f[what[s]].first;
        if (cur > best) {
            best = cur;
            cntBest = f[what[s]].second;
        }
        else if (cur == best) {
            cntBest += f[what[s]].second;
        }
    }

    cout << best << ' ' << cntBest << endl;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> nGood >> nBad) {
        DSU dsu; dsu.init(n);
        FOR(i,1,nGood) {
            int u, v; cin >> u >> v;
            dsu.merge(u, v);
        }
        vector< pair<int,int> > cur;
        FOR(i,1,n) if (dsu.lab[i] < 0) {
            cur.push_back(make_pair(dsu.lab[i], i));
        }
        sort(cur.begin(), cur.end());

        k = SZ(cur);
        FOR(i,1,k) weight[i] = - cur[i-1].first;
//        PR(weight, k);

        memset(ke, 0, sizeof ke);
        FOR(i,1,nBad) {
            int u, v; cin >> u >> v;
            int idu, idv;
            FOR(x,1,k) {
                if (dsu.getRoot(u) == cur[x-1].second) idu = x;
                if (dsu.getRoot(v) == cur[x-1].second) idv = x;
            }
            if (idu != idv) {
                ke[idu][idv] = 1;
                ke[idv][idu] = 1;
            }
            else {
                weight[idu] = -1000111;
            }
        }
        solve();
    }
}
