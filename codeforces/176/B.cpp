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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i<_a; ++i)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; REP(i,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);
const long long BASE = 1000000007;

int ok[1011], n;
long long f[2][100111];
char a[1011], b[1011];

bool check(int t) {
    REP(i,n) {
        if (b[i] != a[t]) return false;
        t++;
        if (t == n) t = 0;
    }
    return true;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (gets(a)) {
        gets(b);
        n = strlen(a);
        REP(i,n) ok[i] = check(i);
//        PR(ok, n);
        int k;
        scanf("%d", &k);
        
        f[0][0] = 1; f[1][0] = 0;
        FOR(i,1,k) {
            f[0][i] = (n-1) * f[1][i-1] % BASE;
            f[1][i] = (f[0][i-1] + (n-2) * f[1][i-1]) % BASE;
        }
        
        ll res = 0;
        if (ok[0]) res = (res + f[0][k]) % BASE;
        FOR(i,1,n-1) if (ok[i])
            res = (res + f[1][k]) % BASE;
        cout << res << endl;
        break;
    }
    return 0;
}
