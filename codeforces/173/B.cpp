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

int m, n;
char a[1011][1011];
int qu[3011], first, last, d[3011];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d\n", &m, &n) == 2) {
        FOR(i,1,m) scanf("%s\n", &a[i][1]);
        FOR(i,1,m+n) d[i] = -1;
        d[m] = 0;
        first = last = 1; qu[1] = m;
        while (first <= last) {
            int u = qu[first++];
            if (u <= m) { // u : row
                FOR(v,1,n) if (a[u][v] == '#') {
                    if (d[m+v] < 0) {
                        d[m+v] = d[u] + 1;
                        qu[++last] = m+v;
                    }
                }
            }
            else {
                int j = u-m;
                FOR(i,1,m) if (a[i][j] == '#') {
                    if (d[i] < 0) {
                        d[i] = d[u] + 1;
                        qu[++last] = i;
                    }
                }
            }
        }
        printf("%d\n", d[1]);
    }
    return 0;
}

