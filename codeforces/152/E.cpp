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
using namespace std;

const double PI = acos(-1.0);
const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};
const int oo = 1000111000;

int a[111][111], m, n;

struct State {
    int mask, u, v;
    State() {}
    State(int u, int v, int mask) : u(u), v(v), mask(mask) {}
};

bool operator < (const State &a, const State &b) {
    if (a.mask != b.mask) return a.mask < b.mask;
    if (a.u != b.u) return a.u < b.u;
    return a.v < b.v;
}

bool outside(int u, int v) {
    if (u < 1 || v < 1 || u > m || v > n) return true;
    return false;
}

set< pair<int, State> > s;
int f[111][111][222], mark[111][111];
State tr[111][111][222], tr2[111][111][222];

#define TWO(x) (1<<(x))
#define CONTAIN(S,x) (S & TWO(x))

char res[111][111];

void trace(State cur) {
//    cout << cur.u << ' ' << cur.v << ' ' << cur.mask << endl;
    if (cur.mask == 0) return ;
    
    res[cur.u][cur.v] = 'X';
    trace(tr[cur.u][cur.v][cur.mask]);
    if (tr2[cur.u][cur.v][cur.mask].mask >= 0) {
        trace(tr2[cur.u][cur.v][cur.mask]);
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int k; scanf("%d%d%d", &m, &n, &k);
    FOR(i,1,m) FOR(j,1,n) scanf("%d", &a[i][j]);
    FOR(i,1,m) FOR(j,1,n) REP(mask,TWO(k)) f[i][j][mask] = oo;
    
    FOR(i,1,k) {
        int u, v; scanf("%d%d", &u, &v);
        mark[u][v] = i;
        f[u][v][TWO(i-1)] = a[u][v];
        s.insert(MP(a[u][v], State(u, v, TWO(i-1))));
    }
    
    while (!s.empty()) {
        State cur = s.begin()->S;
        int l = s.begin()->F;
        s.erase(s.begin());
        if (f[cur.u][cur.v][cur.mask] != l) continue;
        
//        cout << cur.u << ' ' << cur.v << ' ' << cur.mask << "   " << l << endl;
        
        if (cur.mask == TWO(k) - 1) {
            printf("%d\n", l);
            memset(res, '.', sizeof res);
            trace(cur);
            FOR(i,1,m) {
                FOR(j,1,n) printf("%c", res[i][j]);
                puts("");
            }
            return 0;
        }
        
        State next;
        REP(dir,4) {
            next.u = cur.u + di[dir]; next.v = cur.v + dj[dir];
            if (outside(next.u, next.v)) continue;
            if (mark[next.u][next.v])
                next.mask = cur.mask | TWO(mark[next.u][next.v] - 1);
            else next.mask = cur.mask;
            
            int cost = f[cur.u][cur.v][cur.mask] + a[next.u][next.v];
            
            if (f[next.u][next.v][next.mask] > cost) {
                f[next.u][next.v][next.mask] = cost;
                tr[next.u][next.v][next.mask] = cur;
                tr2[next.u][next.v][next.mask] = State(0, 0, -1);
                s.insert(MP(cost, next));
            }
            
            REP(mask2,TWO(k)) if (mask2) if ((mask2 & next.mask) == 0) {
                State savenext = next;
                next.mask = mask2 | next.mask;
                cost = f[cur.u][cur.v][cur.mask] + f[next.u][next.v][mask2];
                if (f[next.u][next.v][next.mask] > cost) {
                    f[next.u][next.v][next.mask] = cost;
                    s.insert(MP(cost, next));
                    tr[next.u][next.v][next.mask] = cur;
                    tr2[next.u][next.v][next.mask] = State(next.u, next.v, mask2);
                }
                next = savenext;
            }
        }
    }
    return 0;
}
