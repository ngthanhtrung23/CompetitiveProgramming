//#pragma comment(linker, "/STACK:66777216")
#include <iomanip>
#include <sstream>
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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);
const int MN = 100111;

struct Edge {
    int u, v, c, index;
} e[MN];

bool operator < (const Edge &a, const Edge &b) {
    return a.c < b.c;
}

int n, m, lab[MN], first[MN];

int getRoot(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
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

bool mark[MN];
int res[MN], num[MN], low[MN], cur;
vector<int> ls;
vector< pair<int,int> > ke[MN];
map< pair<int,int>, int > cnt;

void dfs(int u, int fu) {
    num[u] = low[u] = ++cur;
    REP(i,ke[u].size()) {
        int v = ke[u][i].F;
        if (v == fu) continue;
        if (num[v] < 0) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        }
        else low[u] = min(low[u], num[v]);
    }
    
    REP(i,ke[u].size()) {
        int v = ke[u][i].F;
        if (v == fu) continue;
        if (cnt[MP(u,v)] > 1) continue;
        if (low[v] > num[u]) {
            res[ke[u][i].S] = 2;
        }
    }
}

void solve() {
    cnt.clear();
/*    puts("Solve for graph: ");
    REP(i,ls.size()) {
        int u = ls[i];
        REP(x,ke[u].size()) cout << u << ' ' << ke[u][x].F << endl;
    }*/
    
    REP(i,ls.size()) num[ls[i]] = -1;
    REP(i,ls.size()) {
        int u = ls[i];
        REP(x,ke[u].size()) cnt[MP(u,ke[u][x].F)]++;
    }
    
    REP(i,ls.size()) {
        int u = ls[i];
        if (num[u] < 0) {
            cur = 0;
            dfs(u, -1);
        }
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,m) {
            scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].c);
            e[i].index = i;
        }
        sort(e+1, e+m+1);
        FOR(i,1,n) lab[i] = -1;
        FOR(i,1,m) if (e[i].c == e[i-1].c) first[i] = first[i-1]; else first[i] = i;
        
        e[m+1].c = 1000111000;
        FOR(lastEdge,1,m) if (lastEdge == m || e[lastEdge].c < e[lastEdge+1].c) {
            ls.clear();
            FOR(i,first[lastEdge],lastEdge) {
                int u = e[i].u, v = e[i].v;
                if (getRoot(u) == getRoot(v)) res[e[i].index] = 0;
                else {
                    res[e[i].index] = 1;
                    u = getRoot(u); v = getRoot(v);
                    if (!mark[u]) ls.PB(u);
                    if (!mark[v]) ls.PB(v);
                    ke[u].PB(MP(v, e[i].index));
                    ke[v].PB(MP(u, e[i].index));
                    mark[u] = mark[v] = 1;
                }
            }
            
            solve();
            
            FOR(i,first[lastEdge],lastEdge) {
                int u = e[i].u, v = e[i].v;
                if (getRoot(u) != getRoot(v)) {
                    u = getRoot(u); v = getRoot(v);
                    mark[u] = mark[v] = 0;
                    ke[u].clear();
                    ke[v].clear();
                    merge(getRoot(u), getRoot(v));
                }
            }
        }
        
        FOR(i,1,m)
            if (res[i] == 0) puts("none");
            else if (res[i] == 1) puts("at least one");
            else puts("any");
    }
    return 0;
}
