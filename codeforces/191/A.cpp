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

int n;
char a[1011];
int f[300][300];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d\n", &n) == 1) {
        FOR(x,'a','z') FOR(y,'a','z') f[x][y] = -1000111000;
        FOR(i,1,n) {
            gets(a);
            char y = a[0];
            char z = a[strlen(a)-1];
            FOR(x,'a','z') {
                f[x][z] = max(f[x][z], f[x][y] + (int) strlen(a));
            }
            f[y][z] = max(f[y][z], (int) strlen(a));
        }
        int res = 0;
        FOR(x,'a','z') {
            res = max(res, f[x][x]);
        }
        cout << res << endl;
    }
    return 0;
}
