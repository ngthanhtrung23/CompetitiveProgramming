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
using namespace std;

const double PI = acos(-1.0);

int n, a[1011], res[1011];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    
    res[0] = 1000;
    FOR(i,1,n) {
        int u = a[i], v;
        res[i] = 9999;
        int x = u / 1000, y = (u % 1000) / 100, z = (u % 100) / 10, t = u % 10;
        FOR(cs,0,9) {
            v = cs * 1000 + y * 100 + z * 10 + t;
            if (v >= res[i-1]) res[i] = min(res[i], v);
            v = x * 1000 + cs * 100 + z * 10 + t;
            if (v >= res[i-1]) res[i] = min(res[i], v);
            v = x * 1000 + y * 100 + cs * 10 + t;
            if (v >= res[i-1]) res[i] = min(res[i], v);
            v = x * 1000 + y * 100 + z * 10 + cs;
            if (v >= res[i-1]) res[i] = min(res[i], v);
        }
        if (res[i] == 9999 || res[i] > 2011) {
            puts("No solution");
            return 0;
        }
    }
    FOR(i,1,n) printf("%d\n", res[i]);
    return 0;
}
