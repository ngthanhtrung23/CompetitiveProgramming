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

#define TWO(x) (1<<(x))
#define CONTAIN(S,x) (S & TWO(x-1))
using namespace std;

const double PI = acos(-1.0);

int f[1000111];

bool has(int S, int i, int a, int b, int c) {
    if (i == a && CONTAIN(S, b) && CONTAIN(S, c)) return true;
    if (i == b && CONTAIN(S, a) && CONTAIN(S, c)) return true;
    if (i == c && CONTAIN(S, a) && CONTAIN(S, b)) return true;
    return false;
}

int can(int S, int i) {
    int cnt = 0;
    if (i % 3 == 1 && CONTAIN(S, i+1) && CONTAIN(S, i+2)) cnt++;
    if (i % 3 == 2 && CONTAIN(S, i-1) && CONTAIN(S, i+1)) cnt++;
    if (i % 3 == 0 && CONTAIN(S, i-2) && CONTAIN(S, i-1)) cnt++;
    
    if (has(S, i, 3, 5, 7)) cnt++;
    if (has(S, i, 6, 11, 13)) cnt++;
    if (has(S, i, 9, 14, 16)) cnt++;
    return cnt;
}

void init() {
    FORD(S,TWO(18) - 2,0) {
        f[S] = -1000111000;
        FOR(i,1,18) if (!CONTAIN(S,i)) {
            int u = can(S, i);
            if (u) {
                f[S] = max(f[S], u + f[S + TWO(i-1)]);
            }
            else f[S] = max(f[S], - f[S + TWO(i-1)]);
        }
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    init();
    int n;
    while (scanf("%d", &n) == 1 && n) {
        int k = 0;
        FOR(i,1,n) {
            int u; scanf("%d", &u);
            k |= TWO(u-1);
        }
        if (f[k] > 0) puts("Andy wins");
        else if (f[k] < 0) puts("Ralph wins");
        else puts("Draw");
    }
    return 0;
}
