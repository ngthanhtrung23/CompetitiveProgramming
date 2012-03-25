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

char s[1011];
int f[1011][2];
int cur[1011];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while (gets(s)) {
        int n = strlen(s);
        FOR(i,1,n) if (s[i-1] == '1') cur[i] = 0; else cur[i] = 1;
        
        f[1][cur[1]] = 0;
        f[1][1-cur[1]] = 1;
        
        FOR(i,2,n) FOR(a,0,1) {
            if (a == 0) {
                if (cur[i] == 0) f[i][a] = min(f[i-1][0], f[i-1][1]);
                else f[i][a] = f[i-1][0] + 1;
            }
            else {
                if (cur[i] == 0) f[i][a] = f[i-1][1] + 1;
                else f[i][a] = f[i-1][1];
            }
        }
        cout << min(f[n][0], f[n][1]) << endl;
    }
    return 0;
}
