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

int n, c[55], a[55][55];

vector< pair< pair<int,int>, pair<int,int> > > res;

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &c[i]);
        FOR(i,1,n) {
            FOR(j,1,c[i]) scanf("%d", &a[i][j]);
        }

        res.clear();
        FOR(i,1,n) FOR(j,1,c[i]) {
            int ln = a[i][j];
            int pi = i, pj = j;
            FOR(ii,i,n) FOR(jj,1,c[ii]) if (ii > i || jj > j) {
                if (a[ii][jj] < ln) {
                    ln = a[ii][jj];
                    pi = ii;
                    pj = jj;
                }
            }

            if (pi != i || pj != j) {
                swap(a[i][j], a[pi][pj]);
                res.PB(MP(MP(i,j), MP(pi, pj)));
            }
        }
        printf("%d\n", res.size());
        REP(i,res.size()) printf("%d %d %d %d\n", res[i].F.F, res[i].F.S, res[i].S.F, res[i].S.S);
    }
    return 0;
}
