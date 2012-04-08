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
const int MN = 1000111;

int la, lb, a[MN], b[MN], pos1[MN], pos2[MN];

inline int prev(int x) {
    if (x == 1) return la;
    else return x-1;
}

inline int next(int x) {
    if (x == la) return 1;
    else return x + 1;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d", &la, &lb) == 2) {
        memset(pos1, 0, sizeof pos1);
        memset(pos2, 0, sizeof pos2);
        FOR(i,1,la) {
            scanf("%d", &a[i]);
            pos1[a[i]] = i;
        }
        FOR(i,1,lb) {
            scanf("%d", &b[i]);
            pos2[b[i]] = i;
        }
        int u, v = 0, ii, res = 0, cur, lastRes = 0;
        FOR(i,1,la) if (pos2[a[i]]) { // start at i
            u = pos2[a[i]];
            cur = 1;
            if (!v) v = pos2[a[i]];
            else cur = lastRes - 1;
            ii = i;
//            DEBUG(i);
            ii = i + cur; if (ii > la) ii -= la;
//            cout << u << ' ' << v << ' ' << cur << endl;
            while (pos2[a[ii]]
                    && !((u <= pos2[a[ii]] && pos2[a[ii]] <= v) 
                            || (v < u && (u <= pos2[a[ii]] || pos2[a[ii]] <= v)))) {
                cur++;
                v = pos2[a[ii]];
                ii = next(ii);
            }
//            cout << i << ' ' << cur << endl;
            res = max(res, cur);
            if (cur == 1) v = 0;
            lastRes = cur;
        }
        else v = lastRes = 0;
        printf("%d\n", res);
    }
    return 0;
}
