#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <queue>

#define FOR(i,a,b) for(int i=(a),_b=(b); i <= _b; ++i)
#define FORD(i,a,b) for(int i=(a), _b=(b); i >= _b; --i)
#define REP(i,a) for(int i = 0, _a=(a); i < _a; ++i)
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

int getVal(char v) {
    if (v >= '2' && v <= '9') return v - '2';
    if (v == 'T') return 8;
    if (v == 'J') return 9;
    if (v == 'Q') return 10;
    if (v == 'K') return 11;
    if (v == 'A') return 12;
    return -1;
}

int getSuit(char s) {
    if (s == 'S') return 0;
    if (s == 'D') return 1;
    if (s == 'H') return 2;
    if (s == 'C') return 3;
    return -1;
}

int getNum(string s) {
    int u = getVal(s[0]);
    int v = getSuit(s[1]);
    return v*13 + u;
}

inline bool can(int a, int b) {
    if (a == 52 || b == 52) return false;
    return (a / 13 == b / 13) || (a % 13 == b % 13);
}

bool f[55][55][55][55];
int n, a[55];

void solve() {
    memset(f, false, sizeof f);
    int x = a[n];
    int y = 52; if (n > 1) y = a[n-1];
    int z = 52; if (n > 2) z = a[n-2];
    f[n][x][y][z] = true;

    FORD(i,n,2) FOR(x,0,52) FOR(y,0,52) FOR(z,0,52) if (f[i][x][y][z]) {
        int t = 52;
        if (i > 3) t = a[i-3];
        if (can(x, y)) f[i-1][x][z][t] = true;
        if (can(x, t)) f[i-1][y][z][x] = true;
    }

    bool res = false;
    FOR(x,0,52) FOR(y,0,52) FOR(z,0,52) {
        if (f[1][x][y][z]) {
            res = true;
        }
    }
    if (res) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) {
            string s; cin >> s;
            a[i] = getNum(s);
        }
        solve();
    }
    return 0;
}
