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

const int MN = 100111;
vector<int> ke[MN];
int n, q, getIn[MN], getOut[MN], res[MN], cur;
bool vao[MN];

struct Query {
    int typ, x, y;
} queries[MN];

vector<int> queryAt[MN];

void dfs(int u, int fu) {
    getIn[u] = ++cur;
    for(int v : ke[u]) {
        if (v == fu) continue;
        dfs(v, u);
    }
    getOut[u] = ++cur;
}

int lab[MN];
int getRoot(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
    u = getRoot(u);
    v = getRoot(v);
    if (u == v) return ;
    int x = lab[u] + lab[v];
    if (lab[u] < lab[v]) {
        lab[u] = x;
        lab[v] = u;
    }
    else {
        lab[v] = x;
        lab[u] = v;
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> q) {
        FOR(i,1,n) ke[i].clear();
        cur = 0;
        FOR(i,1,q) {
            cin >> queries[i].typ;
            if (queries[i].typ == 2) cin >> queries[i].x;
            else cin >> queries[i].x >> queries[i].y;
        }
        // First, we build tree
        memset(vao, false, sizeof vao);
        FOR(i,1,q) if (queries[i].typ == 1) {
            ke[queries[i].y].push_back(queries[i].x);
            vao[queries[i].x] = true;
        }
        FOR(i,1,n) if (vao[i] == false) {
            dfs(i, -1);
        }
        // Then, store when we should answer queries 3
        FOR(i,1,q) queryAt[i].clear();
        FOR(i,1,q) {
            if (queries[i].typ == 3) 
                queryAt[queries[i].y].push_back(i);
        }
        // Now answer the queries!
        int n2 = 0;
        memset(lab, -1, sizeof lab);
        FOR(i,1,q) {
            if (queries[i].typ == 1) {
                merge(queries[i].x, queries[i].y);
            }
            else if (queries[i].typ == 2) {
                ++n2;
                int start = queries[i].x;
                for(int id : queryAt[n2]) {
                    int u = queries[id].x;
                    if (getRoot(u) == getRoot(start) && getIn[u] <= getIn[start] && getOut[start] <= getOut[u])
                        res[id] = 1;
                    else res[id] = 0;
                }
            }
        }
        FOR(i,1,q)
            if (queries[i].typ == 3) {
                if (res[i]) cout << "YES"; else cout << "NO";
                cout << endl;
            }
    }
    return 0;
}

