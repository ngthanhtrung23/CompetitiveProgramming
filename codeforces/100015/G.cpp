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

int eu[10111], ev[10111], ec[10111];
long long d[10111];
int n, m, q;

void solve() {
    FOR(i,1,10000) d[i] = 1000111000111LL;
    d[1] = 0;
    FOR(turn,1,n+m+2) {
        FOR(i,1,q)
            d[ev[i]] = min(d[ev[i]], d[eu[i]] + ec[i]);
    }
    FOR(i,1,q)
        if (d[ev[i]] > d[eu[i]] + ec[i]) {
            puts("Impossible");
            return ;
        }
    puts("Possible");
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d%d", &n, &m, &q) == 3 && q) {
        FOR(i,1,q) {
            int u, v, c;
            char c1, c2;
            scanf("%d %d %c%c %d", &u, &v, &c1, &c2, &c);
            if (c1 == '<') {
                ev[i] = u;
                eu[i] = n+v;
                ec[i] = c;
            }
            else {
                eu[i] = u;
                ev[i] = n+v;
                ec[i] = -c;
            }
        }
        solve();
    }
    return 0;
}
