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
const int oo = 1000111000;

set< pair<int,int> > s;
vector< pair< int, pair<int,int> > > ke[1011];
int d[1011];
int n, m, t;

bool check(int val) {
    s.clear();
    FOR(i,1,n) d[i] = oo;
    d[1] = 0;
    s.insert(MP(0,1));
    
    while (!s.empty()) {
        int u = s.begin()->S, l = s.begin()->F;
        s.erase(s.begin());
        if (l != d[u]) continue;
        
        REP(i,ke[u].size()) {
            int v = ke[u][i].F, c = ke[u][i].S.F, x = ke[u][i].S.S;
            if (x > val) continue;
            if (d[v] > d[u] + c) {
                d[v] = d[u] + c;
                s.insert(MP(d[v], v));
            }
        }
    }
    return d[n] <= t;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) ke[i].clear();
        int u, v, c, x;
        while (m--) {
            scanf("%d%d%d%d", &u, &v, &c, &x);
            ke[u].PB(MP(v, MP(c,x)));
            ke[v].PB(MP(u, MP(c,x)));
        }
        scanf("%d", &t);
        int l = 0, r = 1000111, res = r;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        check(res);
        if (d[n] > t) puts("NO");
        else {
            puts("YES");
            printf("%d %d\n", res, d[n]);
        }
    }
    return 0;
}
