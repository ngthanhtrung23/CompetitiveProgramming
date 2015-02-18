#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <string>
#include <cmath>
using namespace std;
#define FOR(i, a, b) for(int i=a; i<=b; i++)
#define DOW(i, a, b) for(int i=a; i>=b; i--)
#define FOREACH(it, c) for(typeof(c.begin()) it=c.begin(); it!=c.end(); it++)
#define RESET(c, val) memset(c, val, sizeof(c))
#define base 1000000007

int m, n;
int xc, xl, yc, yl, c[2][2];
long long r, res, k1, k2;

bool ok(int x1, int y1, int x2, int y2, int x3, int y3) {
    return ((x1-x2)*(y1+y2)+(x2-x3)*(y2+y3)+(x3-x1)*(y3+y1))%2==0;
}
int gcd(int a, int b) {
    if (b==0) return a;
    return gcd(b, a%b);
}
int main() {
    //freopen("test.inp", "r", stdin);
    //freopen("", "w", stdout);
    cin >> m >> n;
    xc=(m+2)/2; xl=(m+1)/2;
    yc=(n+2)/2; yl=(n+1)/2;
    c[0][0]=xc*yc; c[1][1]=xl*yl; c[0][1]=xc*yl; c[1][0]=xl*yc;

    res=0;
    FOR(x1, 0, 1) FOR(y1, 0, 1) if (c[x1][y1]>0) {
        k1=c[x1][y1]; c[x1][y1]--;
        FOR(x2, 0, 1) FOR(y2, 0, 1) if (c[x2][y2]>0) {
            k2=c[x2][y2]; c[x2][y2]--;
            FOR(x3, 0, 1) FOR(y3, 0, 1) if (c[x3][y3]>0)
                if (ok(x1, y1, x2, y2, x3, y3))
                      res=(res+c[x3][y3]*((k1*k2)%base))%base;
            c[x2][y2]++;
        }
        c[x1][y1]++;
    }
    FOR(i, 0, m) FOR(j, 0, n) if (i+j>0) {
        if (i==0) r=j-1, res=(res-r*(m+1)*(n-j+1)*6)%base;
        else if (j==0) r=i-1, res=(res-r*(n+1)*(m-i+1)*6)%base;
        else r=gcd(i, j)-1, res=(res-(((m-i+1)*(n-j+1))%base)*r*12)%base;
    }
    cout << (res+base)%base;
    return 0;
}