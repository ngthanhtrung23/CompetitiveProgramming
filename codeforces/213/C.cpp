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

int n, a[333][333], f[333][333][333];
const int oo = 1000111000;

void update(int &a, int k) {
    a = max(a, k);
}

int main() {
    scanf("%d", &n);
    FOR(i,1,n) FOR(j,1,n) scanf("%d", &a[i][j]);

    FOR(i,1,n) FOR(u,1,n) FOR(v,1,n) f[i][u][v] = -oo;

    f[1][1][1] = a[1][1];
    FOR(i,1,n) {
        FOR(u,1,n) FOR(v,u+1,n) {
            if (v == u+1) update(f[i][u+1][v], f[i][u][v]);
            else update(f[i][u+1][v], f[i][u][v] + a[i][u+1]);
        }
        FOR(u,1,n)
            update(f[i][u+1][u+1], f[i][u][u] + a[i][u+1]);
            
        FOR(u,1,n) FOR(v,u,n-1) {
            update(f[i][u][v+1], f[i][u][v] + a[i][v+1]);
        }
        FOR(u,1,n) FOR(v,u,n)
            update(f[i+1][u][v], f[i][u][v] + a[i+1][u] + ((u != v) ? a[i+1][v] : 0));
    }

    printf("%d\n", f[n][n][n]);
    return 0;
}
