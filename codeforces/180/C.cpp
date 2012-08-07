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
const int MN = 100111;

string s;
int f[MN], g[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> s) {
        int n = s.length();
        s = ' ' + s;
        f[0] = 0;
        FOR(i,1,n) {
            f[i] = f[i-1];
            if (s[i] >= 'a' && s[i] <= 'z') f[i]++;
        }
        g[n+1] = 0;
        FORD(i,n,1) {
            g[i] = g[i+1];
            if (s[i] >= 'A' && s[i] <= 'Z') g[i]++;
        }
        int res = n;
        FOR(i,0,n) {
            res = min(res, f[i] + g[i+1]);
        }
        cout << res << endl;
    }
    return 0;
}
