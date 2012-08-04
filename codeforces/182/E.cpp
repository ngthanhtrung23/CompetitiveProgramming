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
using namespace std;
const double PI = acos(-1.0);

const int BASE = 1000000007;

int n, l;
pair< pair<int,int>, int > a[222];
int f[4011][222];

void update(int &a, int b) {
    a += b;
    if (a >= BASE) a -= BASE;
}

int main() {
    while (scanf("%d%d", &n, &l) == 2) {
        int k = 0;
        FOR(i,1,n) {
            int x, y;
            scanf("%d%d", &x, &y);
            if (x == y) {
                a[++k] = MP(MP(x,y), i);
            }
            else {
                a[++k] = MP(MP(x,y), i);
                a[++k] = MP(MP(y,x), i);
            }
        }
        memset(f, 0, sizeof f);
        n = k;
        FOR(i,1,n) {
            f[a[i].F.F][i] = 1;
        }

        FOR(len,1,l)
        FOR(last,1,n)
        if (f[len][last]) {
            FOR(now,1,n) if (a[now].S != a[last].S && a[now].F.F == a[last].F.S)
                update(f[len + a[now].F.F][now], f[len][last]);
        }

        int res = 0;
        FOR(i,1,n)
            update(res, f[l][i]);
        printf("%d\n", res);
    }
    return 0;
}
