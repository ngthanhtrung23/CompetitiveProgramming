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

long long f[44][44], g[44];

long long getg(int n) {
    if (g[n] >= 0) return g[n];
    if (n == 0) return 1;
    if (n == 1) return 1;
    if (n == 2) return 2;
    long long res = 0;
    FOR(u,1,n) {
        int l = u - 1, r = n - u;
        res += getg(l) * getg(r);
    }
    return g[n] = res;
}

long long get(int n, int k) {
    if (f[n][k] >= 0) return f[n][k];
    if (n == 0) {
        if (k == 0) return 1;
        else return 0;
    }
    if (n == 1) {
        if (k <= 1) return 1;
        else return 0;
    }

    long long res = 0;
    FOR(u,1,n) {
        int l = u - 1, r = n - u;
        res += get(l, k-1)*getg(r) - get(l, k-1)*get(r, k-1) + getg(l)*get(r, k-1);
    }
    return f[n][k] = res;
}

int main() {
    memset(f, -1, sizeof f);
    memset(g, -1, sizeof g);
    int n, h;
    while (cin >> n >> h) {
        cout << get(n, h) << endl;
    }
    return 0;
}
