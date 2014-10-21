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

int mint[33], maxt[33], n, d;

int getMin(int l, int r) {
    int res = 0;
    FOR(i,l,r) res += mint[i];
    return res;
}

int getMax(int l, int r) {
    int res = 0;
    FOR(i,l,r) res += maxt[i];
    return res;
}

int main() {
    while (cin >> d >> n) {
        FOR(i,1,d) cin >> mint[i] >> maxt[i];
        if (getMin(1,d) <= n && n <= getMax(1,d)) {
            puts("YES");
            FOR(i,1,d) {
                FOR(now,mint[i],maxt[i])
                if (getMin(i+1,d) <= n-now && n-now <= getMax(i+1,d)) {
                    n -= now;
                    printf("%d ", now);
                    break;
                }
            }
            puts("");
        }
        else puts("NO");
    }
    return 0;
}