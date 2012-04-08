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

int n, m, a[MN], qu[2*MN], first, last, f[MN], g[MN];
vector< pair<int, int> > ke[MN];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            ke[i].clear();
        }
        int u, v;
        FOR(i,1,m) {
            scanf("%d%d", &u, &v);
            ke[u].PB(MP(v,1));
            ke[v].PB(MP(u,2));
        }
        memset(f, 0, sizeof f);
        memset(g, 0, sizeof g);
        FOR(turn,1,2) {
            int first = 1, last = 0;
            FOR(i,1,n) if (a[i] == turn) {
                qu[++last] = i;
                if (turn == 1) f[i] = 1;
                else g[i] = 1;
            }
            while (first <= last) {
                int u = qu[first++];
                REP(i,ke[u].size()) if (ke[u][i].S == turn) {
                    int v = ke[u][i].F;
                    int cur = (turn == 1) ? f[v] : g[v];
                    if (!cur && a[v] != turn) {
                        if (turn == 1) f[v] = 1; else g[v] = 1;
                        if (a[v] == 0) qu[++last] = v;
                        if (turn == 1) qu[++last] = v;
                    }
                }
            }
        }
//        PR(f, n); PR(g, n);
        FOR(i,1,n) {
            int res = 0;
            if (a[i] == 0) {
                if (f[i] && g[i]) res = 1;
            }
            else if (a[i] == 1) {
                if (g[i]) res = 1;
            }
            else {
                if (f[i]) res = 1;
            }
            printf("%d\n", res);
        }
    }
    return 0;
}
