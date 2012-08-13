#include <sstream>
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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);

int n, f[5011], trace[5011];
pair< pair<int,int>, int > a[5011];

void tr(int u) {
    if (u <= 0) return ;
    tr(trace[u]);
    printf("%d ", a[u].S);
}

int main() {
    int tmp;
    while (scanf("%d", &tmp) == 1) {
        int X, Y;
        scanf("%d%d", &X, &Y);
        n = 0;
        FOR(i,1,tmp) {
            int x, y;
            scanf("%d%d", &x, &y);
            if (x <= X || y <= Y) continue;
            a[++n] = MP(MP(x,y), i);
        }
        sort(a+1, a+n+1);
        FOR(i,1,n) {
            f[i] = 1;
            trace[i] = -1;
            FOR(j,1,i-1)
            if (a[j].F.F < a[i].F.F && a[j].F.S < a[i].F.S) {
                if (f[j]+1 > f[i]) {
                    f[i] = f[j]+1;
                    trace[i] = j;
                }
            }
        }
        int res = 0;
        FOR(i,1,n) {
            res = max(res, f[i]);
        }
        printf("%d\n", res);
        FOR(i,1,n) if (f[i] == res) {
            tr(i);
            puts("");
            break;
        }
    }
    return 0;
}
