#include <iomanip>
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

int n, lab[100111], h[100111], x, y, xy;
vector< pair<int,int> > ke[100111];
int fat[20][100111], cost[20][100111];

int getRoot(int u) {
    if (lab[u] < 0) return u;
    else return lab[u] = getRoot(lab[u]);
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

void dfs(int u, int fu) {
    REP(i,ke[u].size()) {
        int v = ke[u][i].F;
        if (v == fu) continue;
        h[v] = h[u] + 1;
        fat[0][v] = u;
        cost[0][v] = ke[u][i].S;
        dfs(v, u);
    }
}

void init() {
    FOR(i,1,18) {
        FOR(u,1,n) {
            int v = fat[i-1][u];
            if (v == -1) fat[i][u] = -1;
            else {
                fat[i][u] = fat[i-1][v];
                cost[i][u] = cost[i-1][u] + cost[i-1][v];
            }
        }
    }
//    FOR(i,0,2) {
//        FOR(u,1,n) cout << fat[i][u] << ' ';
//        puts("");
//    }
}

int get(int u, int v) {
    int saveu = u, savev = v;
    int res = 0;
    if (h[u] > h[v]) swap(u, v);
    if (h[v] > h[u]) {
        FORD(i,18,0) {
            int x = fat[i][v];
            if (x >= 0 && h[x] >= h[u]) {
                res += cost[i][v];
                v = x;
            }
        }
    }
    // h[v] == h[u]
    if (v != u) {
        FORD(i,18,0) {
            if (fat[i][v] != fat[i][u]) {
                res += cost[i][v] + cost[i][u];
                v = fat[i][v];
                u = fat[i][u];
            }
        }
        res += cost[0][v] + cost[0][u];
    }
    return res;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d", &n) == 1 && n) {
        FOR(i,1,n) {
            lab[i] = -1;
            ke[i].clear();
        }
        FOR(i,1,n) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            u++; v++;
            int saveu = u, savev = v;
            u = getRoot(u); v = getRoot(v);
            if (u != v) {
                merge(u, v);
                ke[saveu].PB(MP(savev,c));
                ke[savev].PB(MP(saveu,c));
            }
            else {
                x = saveu; y = savev; xy = c;
            }
        }
//        cout << x << ' ' << y << ' ' << xy << endl;
        h[1] = 1;
        memset(fat, -1, sizeof fat);
        dfs(1, -1);
        init();
        
        int q; scanf("%d", &q);
        while (q--) {
            int u, v; scanf("%d%d", &u, &v);
            u++; v++;
            printf("%d\n", min(get(u,v), min(get(u, x) + xy + get(y, v), get(u, y) + xy + get(x, v))));
        }
    }
    return 0;
}
