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
using namespace std;

const double PI = acos(-1.0);

int base;
struct Matrix {
    ll a[5][5];
    Matrix operator * (Matrix b) {
        Matrix res;
        REP(i,5) REP(j,5) {
            res.a[i][j] = 0;
            REP(k,5) res.a[i][j] += (a[i][k] * (ll)b.a[k][j]) % base;
        }
        return res;
    }
} p[63];

const int p0[][5] = {{10,0,0,0,9}, {1,1,0,0,0}, {0,0,1,9,1}, {1,1,1,9,1}, {0,0,0,0,1}};

void init() {
    REP(i,5) REP(j,5) p[0].a[i][j] = p0[i][j];
    FOR(i,1,62) p[i] = p[i-1] * p[i-1];
}

int main() {
    freopen("zeroes.in", "r", stdin);
    freopen("zeroes.out", "w", stdout);
    ll k;
    while (cin >> k >> base) {
        if (k == 1) {
            cout << k % base << endl;
            continue;
        }
        k--;
        init();
        Matrix cur;
        REP(i,5) REP(j,5) if (i == j) cur.a[i][j] = 1; else cur.a[i][j] = 0;
        FOR(b,0,62) if (k & (1LL<<(ll)b)) {
            cur = cur * p[b];
        }
        ll res = 9LL * cur.a[2][0] + cur.a[2][2] + cur.a[2][3] + cur.a[2][4];
        cout << res % base;
    }
    return 0;
}
