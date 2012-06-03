
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
#include <bitset>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i<_a; ++i)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
#define PR0(a,n) cout << #a << " = "; REP(i,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

int n, u, r;
ll a[33], b[33], p[33], k[33], cur[33], x[33];
long long res;

void attempt(int turn) {
    if (turn % 2 != u % 2) {
        long long sum = 0;
        FOR(i,1,n) sum += a[i] * (ll) k[i];
        res = max(res, sum);
    }
    if (turn == u+1) return ;
    
    int save[33];
    if (x[turn-1] == 1) {
        x[turn] = 0;
        FOR(i,1,n) save[i] = a[i];
        FOR(i,1,n) a[i] ^= b[i];
        attempt(turn+1);
        FOR(i,1,n) a[i] = save[i];
    }
    x[turn] = 1;
    FOR(i,1,n) save[i] = a[i];
    FOR(i,1,n) a[i] = save[p[i]] + r;
    attempt(turn+1);
    FOR(i,1,n) a[i] = save[i];
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (cin >> n >> u >> r) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) cin >> b[i];
        FOR(i,1,n) cin >> k[i];
        FOR(i,1,n) cin >> p[i];
        x[0] = 1;
        res = -1000111000111000111LL;
        attempt(1);
        cout << res << endl;
    }
    return 0;
}
