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

const long double PI = acos((long double) -1.0);

int n, k;
char s[500111];

void solve2() {
    int r1 = 0;
    REP(i,n) if (s[i] - 'A' != i % 2) ++r1;
    int r2 = 0;
    REP(i,n) if (s[i] - 'A' != 1 - i%2) ++r2;
    if (r1 < r2) {
        printf("%d\n", r1);
        REP(i,n) putchar('A' + i % 2);
    }
    else {
        printf("%d\n", r2);
        REP(i,n) putchar('A' + 1 - i % 2);
    }
}

void solve() {
    int cnt = 0;
    REP(i,n) if (i && s[i] == s[i-1]) {
        s[i] = 'A';
        while (s[i] == s[i-1] || s[i] == s[i+1]) ++s[i];
        ++cnt;
    }
    printf("%d\n", cnt);
    REP(i,n) putchar(s[i]); puts("");
}

int main() {
    while (scanf("%d%d\n", &n, &k) == 2) {
        memset(s, 0, sizeof s);
        gets(s);
        if (k == 2) solve2();
        else solve();
    }
    return 0;
}