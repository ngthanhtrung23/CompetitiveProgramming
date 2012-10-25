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
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; puts("");
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);
const int MN = 100111;

vector< pair<int,int> > ke[MN];
int eu[MN], ev[MN], n;

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,n-1) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].PB(MP(v,i)); ke[v].PB(MP(u,i));
            eu[i] = u;
            ev[i] = v;
        }

        printf("%d\n", n-1);
        FOR(i,1,n-1) {
            printf("2 %d %d\n", eu[i], ev[i]);
        }
        FOR(u,1,n) {
            REP(i,ke[u].size()-1) {
                int x = ke[u][i].S;
                int y = ke[u][i+1].S;
                printf("%d %d\n", x, y);
            }
        }
    }
    return 0;
}
