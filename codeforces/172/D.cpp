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
const int MAXV = 10000000;

int res[MAXV + 10];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    FORD(i,4000,1) {
        int j, ii, now = 1;
        j = ii = i*i;
        while (j <= MAXV) {
            if (!res[j]) res[j] = now;
            ++now;
            j += ii;
        }
    }
    int a, n;
    while (scanf("%d%d", &a, &n) == 2) {
        ll sum = 0;
        FOR(i,a,a+n-1) sum += res[i];
        cout << sum << endl;
    }
    return 0;
}
