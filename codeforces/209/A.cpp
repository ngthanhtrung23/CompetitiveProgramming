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

const int MN = 1000111;
const int BASE = 1000000007;

int f[2][MN], g[2][MN];

int main() {
    int n = 1000000;
    f[0][1] = g[0][1] = 0;
    f[1][1] = g[1][1] = 1;

    FOR(i,2,n) REP(last,2) {
        if ((i & 1) == last) f[last][i] = g[1-last][i-1] + 1;
        g[last][i] = g[last][i-1] + f[last][i];
        if (g[last][i] >= BASE) g[last][i] -= BASE;
    }
    while (cin >> n)
        cout << (g[0][n] + g[1][n]) % BASE << endl;
    return 0;
}
