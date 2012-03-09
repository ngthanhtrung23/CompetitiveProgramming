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
using namespace std;

const double PI = acos(-1.0);
const int MN = 200111;

#define CT(i) ((i) << 1)
#define CP(i) (CT(i) + 1)
struct Node {
    int ln, save, cover;
} it[6*MN];

inline void down(int i) {
    if (it[i].cover) {
        it[CT(i)].cover += it[i].cover;
        it[CT(i)].ln -= it[i].cover;
        
        it[CP(i)].cover += it[i].cover;
        it[CP(i)].ln -= it[i].cover;
        
        it[i].cover = 0;
    }
}

inline void update(int i) {
    if (it[CT(i)].ln > it[CP(i)].ln) {
        it[i].ln = it[CT(i)].ln;
        it[i].save = it[CT(i)].save;
    }
    else {
        it[i].ln = it[CP(i)].ln;
        it[i].save = it[CP(i)].save;
    }
}

int n, m, nLeaf, h[MN], a[MN], first[MN], last[MN], fat[MN], id[MN];
vector<int> ke[MN];

void dfs(int u, int fu) {
    first[u] = nLeaf + 1;
    bool ok = false;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        ok = true;
        fat[v] = u;
        h[v] = h[u] + 1;
        dfs(v, u);
    }
    if (!ok) {
        nLeaf++;
        a[nLeaf] = h[u];
        id[nLeaf] = u;
    }
    last[u] = nLeaf;
}

void init(int i, int l, int r) {
    if (l == r) {
        it[i].cover = 0;
        it[i].ln = a[l];
        it[i].save = l;
        return ;
    }
    int mid = (l + r) >> 1;
    init(CT(i), l, mid);
    init(CP(i), mid+1, r);
    update(i);
}

void update(int i, int l, int r, int u, int v, int k) {
    if (u > v) return ;
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].cover += k;
        it[i].ln -= k;
        return ;
    }
    down(i);
    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u, v, k);
    update(CP(i), mid+1, r, u, v, k);
    update(i);
}

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    while (scanf("%d%d", &n, &m) == 2) {
        memset(it, 0, sizeof it);
        nLeaf = 0;
        FOR(i,1,n) ke[i].clear();
        int u, v;
        FOR(i,2,n) {
            scanf("%d%d", &u, &v);
            ke[u].PB(v); ke[v].PB(u);
        }
        h[1] = 0;
        dfs(1, -1);
//        DEBUG(nLeaf);
//        FOR(i,1,nLeaf) cout << a[i] << ' '; puts("");
//        FOR(i,1,nLeaf) cout << id[i] << ' '; puts("");
        init(1,1,nLeaf);
        int res = 0;
        while (m--) {
            res += it[1].ln;
            int y = it[1].save;
            int x = id[y];
//            DEBUG(x);
//            DEBUG(res);
            
            bool ok = true;
            FORD(dec,it[1].ln,1) {
                if (ok) {
                    ok = false;
//                    DEBUG(x);
//                    cout << "Decrease: " << y << '-' << y << " " << dec << endl;
                    update(1,1,nLeaf,y,y,dec);
                    u = v = y;
                }
                else {
                    x = fat[x];
//                    DEBUG(x);
//                    cout << "Decrease: " << first[x] << '-' << u-1 << " " << dec << endl;
//                    cout << "Decrease: " << (v+1) << '-' << last[x] << " " << dec << endl;
                    update(1,1,nLeaf,first[x],u-1,dec);
                    update(1,1,nLeaf,v+1,last[x],dec);
                    u = first[x]; v = last[x];
                }
            }
            if (res > n-1) res = n-1;
            if (res == n-1) break;
        }
        printf("%d\n", res);
        break;
    }
    return 0;
}
