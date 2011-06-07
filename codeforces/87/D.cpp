#pragma comment(linker, "/STACK:16777216")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>
#include <sstream>
#include <iomanip>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

const double PI = acos(-1.0);

ll res[100111];
int kq[100111], n, lab[100111];
struct rec {
    int u, v, c, id;
} e[100111];

int getRoot(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = getRoot(lab[u]);
}
void merge(int u, int v) {
    u = getRoot(u); v = getRoot(v);
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

void inp() {
    scanf("%d", &n);
    FOR(i,1,n-1) {
        scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].c);
        e[i].id = i;
    }
}

bool operator < (rec a, rec b) {
    return a.c < b.c;
}

vector<int > ke[100111];
ll sl[100111];
int root[100111], h[100111];

void dfs(int u, int fu, int r) {
    root[u] = r;
    sl[u] = -lab[getRoot(u)];
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        if (sl[v] < 0) {
            h[v] = h[u] + 1;
            dfs(v, u, r);
            sl[u] += sl[v];
        }
    }
}

void solve() {
    FOR(i,1,n) ke[i].clear();
    memset(lab, -1, sizeof lab);
    sort(e+1, e+n);
    e[n].c = 1000111000;
    memset(sl, -1, sizeof sl);
    int last = 0;
    FOR(i,1,n-1) if (e[i].c < e[i+1].c) {
//        cout << "At edge: " << e[i].u << ' ' << e[i].v << ' ' << e[i].c << endl;
        FOR(u,last+1,i) {
            getRoot(e[u].u);
            getRoot(e[u].v);
        }
        
        FOR(u,last+1,i) {
            int x = getRoot(e[u].u);
            int y = getRoot(e[u].v);
            ke[x].PB(y);
            ke[y].PB(x);
//            cout << x << ' ' << y << endl;
//            cout << ke[2].size() << ' ' << ke[6].size() << ' ' << ke[13].size() << endl;
        }
        
        FOR(u,last+1,i)
            if (sl[getRoot(e[u].u)] < 0) {
                h[getRoot(e[u].u)] = 1;
                dfs(getRoot(e[u].u), -1, getRoot(e[u].u));
            }
            
        FOR(u,last+1,i) {
            int x = getRoot(e[u].u), y = getRoot(e[u].v);
            if (h[x] > h[y]) swap(x, y);
//            cout << e[u].u << ' ' << e[u].v << ' ' << sl[y] << ' ' << root[x] << ' ' << sl[root[x]] << endl;

            res[e[u].id] = sl[y] * (sl[root[x]] - sl[y]) * 2;
//            cout << e[u].id << ' ' << res[e[u].id] << endl;
        }
        
        FOR(u,last+1,i) {
            ke[getRoot(e[u].u)].clear();
            ke[getRoot(e[u].v)].clear();
            sl[getRoot(e[u].u)] = -1;
            sl[getRoot(e[u].v)] = -1;
            merge(e[u].u, e[u].v);
        }
        last = i;
    }
    
//    FOR(i,1,n-1) cout << res[i] << ' ';
//    cout << endl;
}

void ans() {
    ll ln = 0;
    FOR(i,1,n-1) ln = max(ln, res[i]);
    cout << ln << ' ';
    int cnt = 0;
    FOR(i,1,n-1) if (res[i] == ln) kq[cnt++] = i;
    cout << cnt << endl;
    sort(kq, kq+cnt);
    REP(i,cnt) printf("%d ", kq[i]);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    inp();
    solve();
    ans();
    return 0;
}
