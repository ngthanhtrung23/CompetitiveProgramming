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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);
const int BASE = 1000000007;

string s, t;
int f[5011][5011], sum[5011];

#define update(x) if (x >= BASE) x -= BASE

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    cin >> s >> t;
    int ns = s.length(), nt = t.length();
    REP(i,ns) {
        memset(sum, 0, sizeof sum);
        REP(j,nt) {
            if (i) {
                if (j) sum[j] = sum[j-1] + f[i-1][j];
                else sum[j] = f[i-1][j];
                update(sum[j]);
            }
            if (s[i] == t[j]) {
                if (j) f[i][j] = 1 + sum[j-1];
                else f[i][j] = 1;
                update(f[i][j]);
            }
        }
    }
    int res = 0;
    REP(i,ns) REP(j,nt) {
        res += f[i][j];
        update(res);
    }
    printf("%d\n", res);
    return 0;
}
