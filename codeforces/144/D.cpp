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

int n, m, start, d[100111];
set< pair<int,int> > s;
vector< pair<int,int> > ke[100111];

void ijk(int u) {
    FOR(i,1,n) d[i] = 1000111000;
    d[u] = 0;
    s.insert(MP(0, u));
    while (!s.empty()) {
        int l = s.begin() -> F, u = s.begin() -> S;
        s.erase(s.begin());
        if (l != d[u]) continue;
        
        REP(i,ke[u].size()) {
            int v = ke[u][i].F, c = ke[u][i].S;
            if (d[v] > d[u] + c) {
                d[v] = d[u] + c;
                s.insert(MP(d[v], v));
            }
        }
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d%d%d", &n, &m, &start);
    while (m--) {
        int u, v, c;
        scanf("%d%d%d", &u,&v,&c);
        ke[u].PB(MP(v,c));
        ke[v].PB(MP(u,c));
    }
    int l; scanf("%d", &l);
    ijk(start);
    int res = 0;
    
//    FOR(i,1,n) cout << d[i] << ' '; puts("");
    
    FOR(i,1,n) if (d[i] == l) {
        res++;
    }
    
    FOR(u,1,n) {
        REP(i,ke[u].size()) {
            int v = ke[u][i].F, c = ke[u][i].S;
            if (u > v) continue;
            
            int a = l - d[u];
            int b = c - (l - d[v]);
            
            if (0 < a && a < c && d[u] + a <= d[v] + c-a) res++;
            if (0 < b && b < c && b != a && d[v] + c-b <= d[u] + b) res++;
        }
    }
    printf("%d", res);
    return 0;
}
